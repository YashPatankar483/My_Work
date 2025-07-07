#pragma once
#include <vector>
#include <string>

struct CompiledBlob {
    std::string filepath;                   // Path to the .exe file
    // void* data;
    // size_t size;
    int kernel_id;
};

// The compiler just emits raw compiled blobs
std::vector<CompiledBlob> compile_kernels();
