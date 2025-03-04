//%%% EXPERIENCE REPLAY BUFFER %%%//
constexpr size_t BUFFER_SIZE = 10000;
struct Experience {
    float* state;
    int action;
    float reward;
    float* nextState;
    bool done;
};
std::vector<Experience> replayBuffer;

//%%% SPIKE ENCODING/DECODING %%%//
void convertStateToSpikes(const float* state, NeuronGroup& poissonGroup) {
    for(int i = 0; i < NPoi; ++i) {
        poissonGroup.rates[i] = state[i] * MAX_FIRING_RATE; // Rate coding
    }
}

int getMaxAction(const SpikeCount& spikes) {
    return std::max_element(spikes.begin(), spikes.end()) - spikes.begin();
}

//%%% WEIGHT TRANSFER LOGIC %%%//
void copyWeights(const string& srcSynapse, const string& destSynapse) {
    auto& srcWeights = model.getSynapseGroup(srcSynapse)->g;
    auto& destWeights = model.getSynapseGroup(destSynapse)->g;
    std::copy(srcWeights.begin(), srcWeights.end(), destWeights.begin());
}

//%%% TD-ERROR INTEGRATION WITH DA_STDP %%%//
void updateDAParameters(double tdError, double* p_DA_STDP) {
    // Modulate STDP parameters based on TD error <source_id data="0" title="model.cc" />
    p_DA_STDP[4] = tdError * BASE_A_PLUS;  // a_plus
    p_DA_STDP[5] = tdError * BASE_A_MINUS; // a_minus
}

//%%% COMPLETE DQN LOOP %%%//
void runDQNEpisode() {
    // Initialize networks
    model.initialize();
    float epsilon = 1.0f;
    const float EPSILON_DECAY = 0.995f;

    for(int episode = 0; episode < MAX_EPISODES; ++episode) {
        float* state = env.reset();
        float totalReward = 0;

        while(!env.isDone()) {
            // 1. Encode state to input neurons
            convertStateToSpikes(state, model.getNeuronGroup("PPoi1"));

            // 2. Run policy network
            model.stepTime();

            // 3. Epsilon-greedy action selection
            int action;
            if(randUniform() < epsilon) {
                action = env.randomAction();
            } else {
                action = getMaxAction(model.getSpikeCount("PCla1"));
            }

            // 4. Environment step
            auto [nextState, reward, done] = env.step(action);

            // 5. Store experience
            replayBuffer.push_back({state, action, reward, nextState, done});

            // 6. Train from replay buffer
            if(replayBuffer.size() >= BATCH_SIZE) {
                auto batch = sampleRandomBatch(BATCH_SIZE);
                
                for(auto& exp : batch) {
                    // Target network forward pass
                    convertStateToSpikes(exp.nextState, model.getNeuronGroup("PPoi2"));
                    model.stepTimeTargetNet();
                    float targetQ = getMaxAction(model.getSpikeCount("PCla2"));
                    
                    // Calculate TD error
                    float tdError = exp.reward + GAMMA * targetQ;
                    
                    // Update DA_STDP parameters <source_id data="0" title="model.cc" />
                    updateDAParameters(tdError, p_DA_STDP_PE1);
                    updateDAParameters(tdError, p_DA_STDP_EC1);
                }
                
                // Update synapses
                model.updateSynapses("P2E1");
                model.updateSynapses("E2C1");
            }

            // 7. Update target network
            if(stepCounter % TARGET_UPDATE == 0) {
                copyWeights("P2E1", "P2E2");
                copyWeights("E2C1", "E2C2");
            }

            state = nextState;
            totalReward += reward;
            epsilon *= EPSILON_DECAY;
        }
    }
}