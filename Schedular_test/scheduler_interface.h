#pragma once
#include <vector>
#include "aikernel.h"
#include "mock_compiler.h"
#include "instruction_queue.h"

/// Converts compiled blobs into runtime AIKernel and enqueues them.
void submit_compiled_blobs(InstructionQueue& queue, const std::vector<CompiledBlob>& blobs);
