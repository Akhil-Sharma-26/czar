#pragma once

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

class Tokenizer {
public:
    inline explicit Tokenizer(const std::string src) : m_src(std::move(src)) {}

    inline std::vector<Token> tokenizer(const std::string& str){
        std::string buf;
        std::vector<Token> tokens;

        while(peek().has_value()){
            if(std::isalpha(peek().value())){
                buf.push_back(consume());
                while(peek().has_value() && std::isalnum(peek().value())){
                    buf.push_back(consume());
                }
                if(buf == "return"){
                    tokens.push_back({
                        .type = TokenType::_return
                    });
                    buf.clear();
                } else {
                    std::cerr<<"messed Up return token"<<std::endl;
                    exit(EXIT_FAILURE);
                }
            }
            else if(std::isdigit(peek().value())){
                buf.push_back(consume());
                while(peek().has_value() && std::isdigit(peek().value())){
                    buf.push_back(consume());
                }
                tokens.push_back({
                    .type = TokenType::lit_int,
                    .value = buf
                });
                buf.clear();
            }
            else if( peek().value() == ';'){
                tokens.push_back({
                    .type = TokenType::semi_col
                });
                buf.clear();
                consume();
            }
            else if(isspace(peek().value())) consume();
            else{
                std::cerr<<"messed Up somewhere"<<std::endl;
                exit(EXIT_FAILURE);
            }
        }

        m_indx = 0;
        return tokens;
    }
    
private:
    const std::string m_src; // member source code
    int m_indx = 0; // the curr indx in src code

    // to see what is next char
    // it can be char or end of string
    [[nodiscard]] 
    inline std::optional<char> peek(int ahead = 1) const{ 
        if(m_indx + ahead > m_src.size()){
            return {};
        } else {
            // .at does bounds checking also. [] can result in undefined behaviour
            return m_src.at(m_indx);
        }
    }

    // consume: handle curr
    inline char consume(){
        return m_src.at(m_indx++);
    }
};