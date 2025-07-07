// #include "mock_compiler.h"
// #include <cstdlib>
// #include <cstring>
// #include<iostream>

// std::vector<CompiledBlob> compile_kernels() {

//     static int global_kernel_id = 0;
//     std::vector<CompiledBlob> blobs;

//     int count = 0;        // No of kernels to pass to the scheduler

    
//     std::cout<<"Enter No. of kernels to pass\n";
//     std::cin>>count;

//     for (int i = 0; i < count; ++i) {
//         void* buffer = malloc(256);            // fake compiled data
//         memset(buffer, 42, 256);               // fill with dummy pattern
//         blobs.push_back({ buffer, 256, ++global_kernel_id});
//     }


//     return blobs;    
// }


#include "mock_compiler.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <cstdlib>   // for system()
#include <string>

std::vector<CompiledBlob> compile_kernels() {
    static int global_kernel_id = 0;
    std::vector<CompiledBlob> blobs;

    int count = 0;
    std::cout << "Enter No. of kernels to pass\n";
    std::cin >> count;

    for (int i = 0; i < count; ++i) {
        int kernel_id = ++global_kernel_id;
        std::string base_path = "kernels/";
        std::string filename = "kernel_" + std::to_string(kernel_id);
        std::string source_file = base_path + filename + ".cpp";
        std::string exe_file = base_path + filename + ".exe";

        // Create dummy C++ file
        std::ofstream out(source_file);
        out << "#include <iostream>\n"
            << "int main() {\n"
            << "    std::cout << \"[Compiled Kernel] Running kernel ID: " << kernel_id << "\\n\";\n"
            << "    return 0;\n"
            << "}\n";
        out.close();

        // Compile to .exe using g++
        std::string compile_cmd = "g++ " + source_file + " -o " + exe_file;
        int result = system(compile_cmd.c_str());

        if (result == 0) {
            std::cout << "[Compiler] Generated: " << exe_file << "\n";
            blobs.push_back({ exe_file, kernel_id });
        } else {
            std::cerr << "[Compiler] Failed to compile " << source_file << "\n";
        }
    }

    return blobs;
}
