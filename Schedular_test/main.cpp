#include <thread>
#include "instruction_queue.h"
#include "runtime_executor.h"
#include <cstdlib>
#include <cstring>
#include <chrono>
#include "mock_compiler.h"
#include <iostream>
#include "driver_interface.h"

int main() {
    InstructionQueue iq;
    // background thread waiting to pop and process kernels from the queue.
    std::thread exec_thread(runtime_executor, std::ref(iq));

    std::vector<int> kernel_sequence;               // For testing

    while(true) {
        bool choice;

        std::cout<<"Pass kernels: Press 1 for Yes and 0 for No\n";
        std::cin>>choice;

        if(choice) {

            std::vector<CompiledBlob> blobs = compile_kernels();

            for(int i=0; i<blobs.size(); ++i) {
                
                iq.push({blobs[i].data, blobs[i].size, blobs[i].kernel_id});
                std::this_thread::sleep_for(std::chrono::milliseconds(50));
                kernel_sequence.push_back(blobs[i].kernel_id);

            }
            
        }
        else {
            std::cout<<"\n____________________________________________________________________________________________________________\n";
            std::cout<<"Kernel sequence from compiler: \n";
            for(int i=0; i<kernel_sequence.size(); ++i) {
                std::cout<<"Kernel ID: " << kernel_sequence[i]<< "|";
            }
            std::cout<<"\n";
            print_executed_kernels();
        }

    }

    return 0;
}
