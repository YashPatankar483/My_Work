#pragma once
#include <queue>
#include <atomic>
#include <vector>
#include "aikernel.h"

class InstructionQueue {
private:
    std::queue<AIKernel> queue;
    std::atomic<bool> busy;
    std::vector<int> sequence;   // For test

public:
    InstructionQueue();
    void push(const AIKernel& kernel);
    bool pop(AIKernel& kernel);
    void print_queues();
    bool empty();
};
