#include "aikernel.h"
#include <iostream>
#include "driver_interface.h"
#include <chrono>
#include <thread>

static bool busy = false;
static auto last = std::chrono::steady_clock::now();

bool is_device_idle() {
    auto now = std::chrono::steady_clock::now();
    if (busy && std::chrono::duration_cast<std::chrono::milliseconds>(now - last).count() > 100) {
        busy = false;
    }
    return !busy;
}

void submit_kernel_to_driver(const AIKernel& kernel) {
    std::cout << "[MockDevice] Executing kernel (Kernel ID: "<<kernel.kernel_id << ") of size " << kernel.size << " bytes...\n";
    std::this_thread::sleep_for(std::chrono::milliseconds(10));
    busy = true;
    last = std::chrono::steady_clock::now();
}
