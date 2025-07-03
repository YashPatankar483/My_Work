# Kernel Scheduler

## Program Files
| Component          | Role                                                           |
| ------------------ | -------------------------------------------------------------- |
| `main.cpp`         | Submits fake kernels to the queue                              |
| `InstructionQueue` | A thread-safe queue holding pending kernels                    |
| `runtime_executor` | A background thread that dequeues and sends jobs to the device |
| `mock_device`      | Simulates hardware behavior (busy/idle, execution)             |
