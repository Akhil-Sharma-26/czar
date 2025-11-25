#pragma once

#include "./tokenization.hpp"

struct nodeExpr{
    Token int_lit;
};

struct nodeExit{
    nodeExpr expr;
};

class Parser{
public:
    inline explicit Parser(std::vector<Token> tokens)
    : m_tokens(std::move(tokens)){}

    std::optional<nodeExpr> parse_expr(){
        if(peek().has_value() && peek().value().type == TokenType::lit_int){
            return nodeExpr{.int_lit = consume()};
        }
        return {};
    }

    std::optional<nodeExit> parse(){
        std::optional<nodeExit> exit_node;
        while(peek().has_value()){
            if(peek().value().type == TokenType::_return){
                consume(); // consume either way
                if(auto node_expr = parse_expr()){
                    // handling the expr which was inside the node
                    exit_node = nodeExit{
                        .expr = node_expr.value()
                    };
                }
                else{
                    std::cerr<<"Invalid Expr"<<std::endl;
                    exit(EXIT_FAILURE);
                }

                if(peek().has_value() && peek().value().type == TokenType::semi_col){
                    consume();
                }
                else{
                    std::cerr<<"Invalid Expr"<<std::endl;
                    exit(EXIT_FAILURE);
                }
            }
        }
        m_indx = 0;
        return exit_node;
    }
private:
    [[nodiscard]] 
    inline std::optional<Token> peek(int ahead = 1) const{ 
        if(m_indx + ahead > m_tokens.size()){
            return {};
        } else {
            // .at does bounds checking also. [] can result in undefined behaviour
            return m_tokens.at(m_indx);
        }
    }

    // consume: handle curr
    inline Token consume(){
        return m_tokens.at(m_indx++);
    }

    const std::vector<Token> m_tokens;
    size_t m_indx = 0;
};