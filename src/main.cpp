#include <iostream>
#include <string>
#include <filesystem>
#include <fstream>
#include <optional>
#include <vector>

// Feature detection for C++23
#if __has_include(<version>)
    #include <version>
#endif

// Tokens
enum class TokenType{
    _return,
    lit_int,
    semi_col
};

struct Token{
    TokenType type;
    std::optional<std::string> value;
};

std::vector<Token> tokenizer(const std::string& str){
    std::string buf;
    std::vector<Token> tokens;
    for(int i=0;i<str.size();i++){
        char c = str.at(i);
        if(isalpha(c)){
            buf.push_back(c);
            i++;
            while(isalnum(str.at(i))){
                buf.push_back(str.at(i));
                i++;
            }
            i--;

            if(buf == "return"){
                tokens.push_back({
                    .type = TokenType::_return
                });
                buf.clear();
            }
            else{
                std::cerr<<"messed Up return token"<<std::endl;
                exit(EXIT_FAILURE);
            }
        }
        else if (isdigit(c)){
            while(isdigit(str[i])){
                buf.push_back(str.at(i));
                std::cout<<buf<<std::endl;
                i++;
            } i--;
            tokens.push_back({
                .type = TokenType::lit_int,
                .value = buf
            });
            buf.clear();
        }
        else if(c == ';'){
            tokens.push_back({
                .type = TokenType::semi_col
            });
            buf.clear();
        }
        else if(isspace(c)) continue;
        else{
            std::cerr<<"messed Up somewhere"<<std::endl;
            exit(EXIT_FAILURE);
        }
    }
    std::cout<<tokens.size()<<std::endl;
    return tokens;
}

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

    std::vector<Token> tokens = tokenizer(content);
    

    {
        std::fstream asm_file(std::filesystem::path("./out.asm").string(), std::ios::out);
        asm_file << tokens_to_asm(tokens);
    }

    system("nasm -felf64 out.asm");
    system("ld -o out out.o");

    return EXIT_SUCCESS;
}
