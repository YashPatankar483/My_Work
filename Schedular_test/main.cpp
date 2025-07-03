#include <thread>
#include "instruction_queue.h"
#include "runtime_executor.h"
#include <cstdlib>
#include <cstring>
#include <chrono>
#include "mock_compiler.h"
#include <iostream>

int main() {
    InstructionQueue iq;
    // background thread waiting to pop and process kernels from the queue.
    std::thread exec_thread(runtime_executor, std::ref(iq));

    // background thread behaving as a compiler, creating kernels and passing to the scheduler
    // std::thread compiler_thread(compile_kernels);

    // for (int i = 0; i < 5; ++i) {
    //     void* data = malloc(256);
    //     memset(data, 0, 256);
    //     iq.push({ data, 256 });
    //     std::this_thread::sleep_for(std::chrono::milliseconds(50));
    // }

    // exec_thread.join(); // In real systems this would run forever.

    while(true) {
        bool choice;

        std::cout<<"Pass kernels: Press 1 for Yes and 0 for No\n";
        std::cin>>choice;

        if(choice) {

            std::vector<CompiledBlob> blobs = compile_kernels();

            for(int i=0; i<blobs.size(); ++i) {
                
                iq.push({blobs[i].data, blobs[i].size, blobs[i].kernel_id});
                std::this_thread::sleep_for(std::chrono::milliseconds(50));

            }
            
        }
    }

    return 0;
}
