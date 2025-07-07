#include "aikernel.h"
#include <iostream>
#include "driver_interface.h"
#include <chrono>
#include <thread>
#include <vector>
#include <algorithm>

static bool busy = false;
static auto last = std::chrono::steady_clock::now();
std::vector<int> executed_kernel_ids;

bool is_device_idle() {
    auto now = std::chrono::steady_clock::now();
    if (busy && std::chrono::duration_cast<std::chrono::milliseconds>(now - last).count() > 100) {
        busy = false;
    }
    return !busy;
}

void submit_kernel_to_driver(const AIKernel& kernel) {

    executed_kernel_ids.push_back(kernel.kernel_id);  // Track order

    // std::cout << "[MockDevice] Executing kernel (Kernel ID: "<<kernel.kernel_id <</* ") of size "<<kernel.size<<" bytes...*/"\n";
    // std::this_thread::sleep_for(std::chrono::milliseconds(10));

    // Construct Windows-friendly path
    std::string path = kernel.filepath;  // Ex: "kernels/kernel_1.exe"
    std::replace(path.begin(), path.end(), '/', '\\');  // Convert to backslashes

    std::cout << "[MockDevice] Launching kernel ID: " << kernel.kernel_id
              << " at path: " <<kernel.filepath << "\n";

    int result = system(path.c_str());  // 👈 Run the .exe

    if (result != 0) {
        std::cerr << "[MockDevice] Failed to execute " << kernel.filepath << "\n";
    } 
    else {
        std::cout << "[MockDevice] Finished executing kernel ID: " << kernel.kernel_id << "\n";
    }
    
    busy = true;
    last = std::chrono::steady_clock::now();
}

void print_executed_kernels() {

    std::cout<<"\n";
    std::cout<<"List of Kernels executed by the accelerator in order: \n";
    for (int i=0; i<executed_kernel_ids.size(); ++i) {
        
        std::cout<<"Kernel ID: "<<executed_kernel_ids[i]<< "|";

    }
    std::cout<<"\n____________________________________________________________________________________________________________\n";
    std::cout<<"\n";
}