#include "mock_compiler.h"
#include <cstdlib>
#include <cstring>
#include<iostream>

std::vector<CompiledBlob> compile_kernels() {

    static int global_kernel_id = 0;
    std::vector<CompiledBlob> blobs;

    int count = 0;        // No of kernels to pass to the scheduler

    
    std::cout<<"Enter No. of kernels to pass\n";
    std::cin>>count;

    for (int i = 0; i < count; ++i) {
        void* buffer = malloc(256);            // fake compiled data
        memset(buffer, 42, 256);               // fill with dummy pattern
        blobs.push_back({ buffer, 256, ++global_kernel_id});
    }


    return blobs;    
}
