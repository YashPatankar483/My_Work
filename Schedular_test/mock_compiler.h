#pragma once
#include <vector>

struct CompiledBlob {
    void* data;
    size_t size;
    int kernel_id;
};

// The compiler just emits raw compiled blobs
std::vector<CompiledBlob> compile_kernels();
