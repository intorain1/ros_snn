// ExperienceBuffer.h
#ifndef EXPERIENCE_BUFFER_H
#define EXPERIENCE_BUFFER_H

#include <vector>
#include <cuda_runtime.h>

struct Experience {
    float* state_spikes;  // Spike pattern from PPoi1/PPoi2 <source_id data="0" title="model.cc" />
    int action;           // Action index from PCla output <source_id data="0" title="model.cc" />
    float reward;
    float* next_spikes;   // Next state PPoi spikes <source_id data="0" title="model.cc" />
    bool done;
};

class ExperienceBuffer {
public:
    ExperienceBuffer(size_t capacity);
    ~ExperienceBuffer();
    
    void store(const Experience& exp);
    std::vector<Experience> sample(size_t batch_size);

private:
    std::vector<Experience> buffer_;
    size_t capacity_;
};

#endif // EXPERIENCE_BUFFER_H