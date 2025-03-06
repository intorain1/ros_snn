// DSQN.cc
#include <vector>
#include <deque>
#include <random>
#include <algorithm>
#include <cuda_runtime.h>
#include "model.h"
#include "buffer.cc"

// GeNN生成的头文件
#include "model_CODE/definitions.h"

constexpr size_t BATCH_SIZE = 4;
constexpr float GAMMA = 0.9f;
constexpr float LR = 0.2f;
constexpr size_t BUFFER_SIZE = 100;

class QLearningAgent {
private:
    ExperienceBuffer buffer_;
    float gamma_;
    float epsilon_;
    float lr_;
    
public:
    QLearningAgent(size_t buffer_size, float gamma, float lr) 
        : buffer_(buffer_size), gamma_(gamma), lr_(lr), epsilon_(0.8f) {}

    int selectAction(float* state_spikes) {
        if (static_cast<float>(rand()) / RAND_MAX > epsilon_) {
            pushSpikesToGeNN(state_spikes);
            stepTimeGPU();
            return readOutputAction();
        } 
        else {
            return rand() % 2;
        }
    }

    void optimizeModel() {
        if (buffer_.size() < BATCH_SIZE) return;
        auto batch = buffer_.sample(BATCH_SIZE);
        
        float* d_states;
        float* d_next_states;
        cudaMalloc(&d_states, BATCH_SIZE * NPoi * sizeof(float));
        cudaMalloc(&d_next_states, BATCH_SIZE * NPoi * sizeof(float));

        for (size_t i=0; i<BATCH_SIZE; ++i) {
            cudaMemcpy(d_states+i*NPoi, batch[i].state_spikes, 
                      NPoi*sizeof(float), cudaMemcpyHostToDevice);
            cudaMemcpy(d_next_states+i*NPoi, batch[i].next_spikes,
                      NPoi*sizeof(float), cudaMemcpyHostToDevice);
        }

        computeQValues(d_states);
        computeTargetQValues(d_next_states);

        updateWeights();
        cudaFree(d_states);
        cudaFree(d_next_states);
    }
    void updateTargetNet() {
        copyPolicyToTargetGPU(); // GeNN内置参数拷贝函数
    }

    void storeExperience(const Experience& exp) {
        buffer_.store(exp);
    }

    void computeQValues(float* d_states);
    void computeTargetQValues(float* d_next_states);
    void updateWeights();
};

// 主训练循环
void trainLoop(rosbag::Bag& bag) {
    QLearningAgent agent(BUFFER_SIZE, GAMMA, LR);
    float current_reward = 0.0f;
    std::vector<int> action_history;

    for (auto& msg : rosbag::View(bag)) {
        if (msg.isType<dvs_msgs::EventArray>()) {
            auto events = msg.instantiate<dvs_msgs::EventArray>();

            float* d_spikes;
            cudaMallocManaged(&d_spikes, NPoi*sizeof(float));
            generateSpikeTensor(events, d_spikes);
            int action = agent.selectAction(d_spikes);

            float reward = getRewardFromEnvironment();
            current_reward += reward;

            float* d_next_spikes = getNextStateFromGPU();
            agent.storeExperience({d_spikes, action, reward, d_next_spikes});

            // 优化模型
            if (current_reward > 500) {
                agent.optimizeModel();
                agent.updateTargetNet();
                current_reward = 0;
            }

            cudaFree(d_spikes);
        }
    }
}

// GeNN网络初始化
void initializeGeNNModel() {
    modelDefinition(model);
    allocateMem();
    initialize();

    if (exists("weights.bin")) {
        loadWeightsFromFile("weights.bin");
    }
}

// 主函数
int main(int argc, char** argv) {
    initializeGeNNModel();

    rosbag::Bag bag;
    bag.open("dsec_zurich_city_04_a.bag", rosbag::bagmode::Read);
    trainLoop(bag);
    saveWeightsToFile("weights_final.bin");
    freeMem();
    bag.close();
    return 0;
}