#include "mock_compiler.h"
#include <cstdlib>
#include <cstring>
#include<iostream>

std::vector<CompiledBlob> compile_kernels() {
    std::vector<CompiledBlob> blobs;

    int count = 0;        // No of kernels to pass to the scheduler
    bool choice;

    std::cout<<"Do you want to pass kernels (1/0)\n";
    std::cin>>choice;

    if(choice) {
        std::cout<<"Enter No. of kernels to pass\n";
        std::cin>>count;

        for (int i = 0; i < count; ++i) {
            void* buffer = malloc(256);            // fake compiled data
            memset(buffer, 42, 256);               // fill with dummy pattern
            blobs.push_back({ buffer, 256 });
        }

    }

    return blobs;    
}
