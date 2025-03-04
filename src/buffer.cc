// ExperienceBuffer.cc
#include "ExperienceBuffer.h"
#include <algorithm>
#include <random>

ExperienceBuffer::ExperienceBuffer(size_t capacity) 
    : capacity_(capacity) {}

ExperienceBuffer::~ExperienceBuffer() {
    for(auto& exp : buffer_) {
        cudaFreeHost(exp.state_spikes);
        cudaFreeHost(exp.next_spikes);
    }
}

void ExperienceBuffer::store(const Experience& exp) {
    if(buffer_.size() >= capacity_) {
        cudaFreeHost(buffer_<source_id data="0" title="model.cc" />.state_spikes);
        cudaFreeHost(buffer_<source_id data="0" title="model.cc" />.next_spikes);
        buffer_.erase(buffer_.begin());
    }

    float *d_state, *d_next;
    cudaMallocHost(&d_state, NPoi*sizeof(float));
    cudaMallocHost(&d_next, NPoi*sizeof(float));
    
    cudaMemcpy(d_state, exp.state_spikes, NPoi*sizeof(float), cudaMemcpyDeviceToHost);
    cudaMemcpy(d_next, exp.next_spikes, NPoi*sizeof(float), cudaMemcpyDeviceToHost);
    
    buffer_.push_back({d_state, exp.action, exp.reward, d_next, exp.done});
}

std::vector<Experience> ExperienceBuffer::sample(size_t batch_size) {
    std::vector<Experience> batch;
    if(buffer_.empty()) return batch;

    size_t actual_size = std::min(batch_size, buffer_.size());
    batch.reserve(actual_size);

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<size_t> dist(0, buffer_.size()-1);

    for(size_t i = 0; i < actual_size; ++i) {
        const auto& src = buffer_[dist(gen)];
        
        float *d_state, *d_next;
        cudaMallocHost(&d_state, NPoi*sizeof(float));
        cudaMallocHost(&d_next, NPoi*sizeof(float));
        
        memcpy(d_state, src.state_spikes, NPoi*sizeof(float));
        memcpy(d_next, src.next_spikes, NPoi*sizeof(float));
        
        batch.push_back({d_state, src.action, src.reward, d_next, src.done});
    }

    return batch;
}