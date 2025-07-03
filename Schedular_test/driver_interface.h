#pragma once
#include "aikernel.h"

bool is_device_idle();
void submit_kernel_to_driver(const AIKernel& kernel);
