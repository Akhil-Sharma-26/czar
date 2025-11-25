#pragma once

#include "./tokenization.hpp"
#include <variant>
struct NodeExprIntLit{
    Token int_lit;
};

struct NodeExprIdent{
    Token ident;
};

struct NodeExpr{
    std::variant<NodeExprIdent, NodeExprIntLit> var; // tagged union, Finds the type which has the largest size and allocates that much space + some space to check what type it is!
};

struct NodeStatementExit{
    NodeExpr expr;
};

struct NodeStatementManlo{
    Token ident;
    NodeExpr expr;
};

struct NodeStatements{
    std::variant<NodeStatementExit, NodeStatementManlo> var;
};

struct NodeProg{
    std::vector<NodeStatements> stmts;
};

class Parser{
public:
    inline explicit Parser(std::vector<Token> tokens)
    : m_tokens(std::move(tokens)){}

    std::optional<NodeExpr> parse_expr(){
        if(peek().has_value() && peek().value().type == TokenType::lit_int){
            return NodeExpr{
                .var = 
                    NodeExprIntLit {
                        .int_lit = consume()
                    }
            };
        }
        else if (peek().has_value() && peek().value().type == TokenType::ident){
            return NodeExpr {
                .var = 
                    NodeExprIdent {
                        .ident = consume()
                    }
            };
        }
        return {};
    }

    std::optional<NodeStatements> parse_stmt(){
        if(peek().value().type == TokenType::_return && peek(1).has_value() && peek(1).value().type == TokenType::open_param){
            consume(); // consume return 
            consume(); // consume (

            NodeStatementExit exit_stmt;
            if(auto node_expr = parse_expr()){
                exit_stmt = NodeStatementExit {
                    .expr = node_expr.value()
                };
            }
            else{
                std::cerr<<"Invalid Expr"<<std::endl;
                exit(EXIT_FAILURE);
            }

            if(peek().has_value() && peek().value().type == TokenType::close_param){
                consume();
            }
            else{
                std::cerr<<"Expected ')' here"<<std::endl;
                exit(EXIT_FAILURE);
            }


            if(peek().has_value() && peek().value().type == TokenType::semi_col){
                consume();
            }
            else{
                std::cerr<<"Expected a semi-colon here"<<std::endl;
                exit(EXIT_FAILURE);
            }

            return NodeStatements {.var = exit_stmt };
        }
        else if(peek().has_value() && peek().value().type == TokenType::maanlo && peek(1).has_value() && peek(1).value().type == TokenType::ident && peek(2).has_value() && peek(2).value().type == TokenType::eq ){
            consume(); // consume let
            auto state_maanlo = NodeStatementManlo {
                .ident = consume() // consume ident
            };
            consume(); // consume =
            if(auto expr = parse_expr()){
                state_maanlo.expr = expr.value();
            } else {
                std::cerr<<"invalid expr 2"<<std::endl;
                exit(EXIT_FAILURE);
            }
            
            if(peek().has_value() && peek().value().type == TokenType::semi_col){
                consume();
            }
            else{
                std::cerr<<"Expected ;"<<std::endl;
                exit(EXIT_FAILURE);
            }

            return NodeStatements {
                .var = state_maanlo
            };
        }
        else {
            return {};
        }
    }

    std::optional<NodeProg> parse_prog(){
        NodeProg prog; // inits the statementes hopefully
        while(peek().has_value()){
            if( auto stmt = parse_stmt()){
                prog.stmts.push_back(stmt.value());
            } else{
                std::cerr<<"Invaid Statmetn"<<std::endl;
                exit(EXIT_FAILURE);
            }
        }
        return prog;
    }
private:
    [[nodiscard]] 
    inline std::optional<Token> peek(int ahead = 0) const{ 
        if(m_indx + ahead >= m_tokens.size()){
            return {};
        } else {
            // .at does bounds checking also. [] can result in undefined behaviour
            return m_tokens.at(m_indx + ahead);
        }
    }

    // consume: handle curr
    inline Token consume(){
        return m_tokens.at(m_indx++);
    }

    const std::vector<Token> m_tokens;
    size_t m_indx = 0;
};