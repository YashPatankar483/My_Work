#include "instruction_queue.h"
#include <iostream>

InstructionQueue::InstructionQueue() : busy(false) {}

void InstructionQueue::push(const AIKernel& kernel) {
    while (busy.exchange(true)); // Spinlock
    queue.push(kernel);
    busy.store(false);
    std::cout<<"Kernel(Kernel ID- " << kernel.kernel_id << ") queued for offloading to accelerator\n";
}

bool InstructionQueue::pop(AIKernel& kernel) {
    while (busy.exchange(true));
    if (queue.empty()) {
        busy.store(false);
        return false;
    }
    kernel = queue.front();
    queue.pop();
    busy.store(false);
    std::cout<<"Kernel(Kernel ID:" << kernel.kernel_id << ") offloaded to accelerator\n";
    return true;
}

bool InstructionQueue::empty() {
    while (busy.exchange(true));
    bool isEmpty = queue.empty();
    busy.store(false);
    std::cout<<"Queue is empty!\n";

    return isEmpty;
}
