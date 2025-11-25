#pragma once

#include "./parser.hpp"

class Generator{
public:
    inline Generator(std::optional<nodeExit> node_exit) : m_nodeExit(node_exit) {};

    std::string generate(){
        std::stringstream output;
        output << "global _start:\n_start:\n";
        output << "    mov rax, 60\n";
        output << "    mov rdi, " << m_nodeExit.value().expr.int_lit.value.value() << "\n";
        output << "    syscall";
        return output.str();
    }

private:
    std::optional<nodeExit> m_nodeExit;
};