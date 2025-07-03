#include "instruction_queue.h"
#include "runtime_executor.h"
#include <thread>
#include <cstdlib>
#include <cstring>

int main() {
    InstructionQueue iq;

    std::thread executor(runtime_executor, std::ref(iq));

    // Simulate enqueuing dummy kernels
    for (int i = 0; i < 5; ++i) {
        void* data = malloc(256);
        memset(data, 0, 256);
        iq.push({ data, 256 });
    }

    executor.join(); // Only for testing; not in real systems
    return 0;
}
