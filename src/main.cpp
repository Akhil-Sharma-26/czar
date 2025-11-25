#include "./tokenization.hpp"



// straight going from tokens
std::string tokens_to_asm(const std::vector<Token>& tokens){
    std::stringstream output;
    output << "global _start:\n_start:\n";
    for(size_t i=0;i<tokens.size();i++){
        const Token& token = tokens[i];
        if(token.type == TokenType::_return){
            if(i+1 < tokens.size() && tokens[i+1].type == TokenType::lit_int){
                if(i+2 < tokens.size() && tokens[i+2].type == TokenType::semi_col){
                    output << "    mov rax, 60\n";
                    output << "    mov rdi, " << tokens[i+1].value.value() << "\n";
                    output << "    syscall";
                }
            }
        }
    }

    return output.str();
}


int main(int argc, char* argv[]) {
    std::cout << "Czar Compiler v0.1.0\n\n" << std::endl ;
    
    if (argc != 2 ) {
        std::cout << "Usage: czar <input_file>" << std::endl;
        return EXIT_FAILURE;   
    }

    std::string content;
    {
        std::stringstream file_content;
        std::fstream ins(std::filesystem::path(
            argv[1]).string(), std::ios::in
        );
        file_content << ins.rdbuf(); // reads who file as once
        content = file_content.str();
    }

    Tokenizer Tokenizer(std::move(content));
    std::vector<Token> tokens = Tokenizer.tokenizer(content);
    

    {
        std::fstream asm_file(std::filesystem::path("./out.asm").string(), std::ios::out);
        asm_file << tokens_to_asm(tokens);
    }

    system("nasm -felf64 out.asm");
    system("ld -o out out.o");

    return EXIT_SUCCESS;
}
