#include "runtime_executor.h"
#include <thread>
#include <chrono>
#include <iostream>
#include "driver_interface.h"

void runtime_executor(InstructionQueue& iq) {
    while (true) {
        AIKernel kernel;
        if (!iq.pop(kernel)) {
            std::this_thread::sleep_for(std::chrono::milliseconds(10));
            continue;
        }

        while (!is_device_idle()) {
            std::this_thread::sleep_for(std::chrono::milliseconds(10));
        }

        submit_kernel_to_driver(kernel);
    }
}

// Pop and offload
