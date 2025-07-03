#pragma once
#include <vector>

struct CompiledBlob {
    void* data;
    size_t size;
};

// The compiler just emits raw compiled blobs
std::vector<CompiledBlob> compile_kernels();
