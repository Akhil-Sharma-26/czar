#include <iostream>
#include <string>
#include <version>

int main(int argc, char* argv[]) {
    std::cout << "Czar Compiler v0.1.0" << std::endl;
    
    #ifdef __cpp_lib_format
        std::cout << "C++23 support detected (std::format available)" << std::endl;
    #else
        std::cout << "C++23 partial support" << std::endl;
    #endif
    
    if (argc > 1) {
        std::cout << "Input file: " << argv[1] << std::endl;
    } else {
        std::cout << "Usage: czar <input_file>" << std::endl;
    }
    
    return 0;
}
