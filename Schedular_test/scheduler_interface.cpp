#include "scheduler_interface.h"

void submit_compiled_blobs(InstructionQueue& queue, const std::vector<CompiledBlob>& blobs) {
    for (const auto& blob : blobs) {
        AIKernel kernel = { blob.data, blob.size };
        queue.push(kernel);
    }
}
