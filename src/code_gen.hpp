#pragma once

#include "./parser.hpp"

class Generator{
public:
    inline Generator(NodeProg prog) : m_prog(std::move(prog)) {};

    void gen_expr(const NodeExpr& expr)  {
        
        struct ExprVisitor {
            Generator* gen;

            void operator()( const NodeExprIntLit& expr_int_lit){
                gen->m_output << "    mov rax, "<<expr_int_lit.int_lit.value.value() << "\n";
                gen->m_output << "    push rax\n";
            }
            void operator()( const NodeExprIdent& expr_ident){

            }
        };

        ExprVisitor visitor{ .gen = this};
        std::visit(visitor, expr.var);
    }


    void gen_stmt(const NodeStatements& stmt)  {
        struct StmtVisitor {
            Generator* gen;
            void operator()(const NodeStatementExit& stmt_exit) const{ //1 
                gen->gen_expr(stmt_exit.expr);
                gen->m_output << "    mov rax, 60\n";
                gen->m_output << "    pop rdi\n";
                gen->m_output << "    syscall\n";
            }
            void operator()(const NodeStatementManlo& stmt_manloo){ //2>

            }
        };

        StmtVisitor visitor {.gen = this};
        std::visit(visitor, stmt.var); // it will call the exit the 1 oand if manlo then call 2
    }

    [[nodiscard]] std::string gen_code(){
        m_output << "global _start:\n_start:\n";
        
        for(const NodeStatements& st: m_prog.stmts){
            gen_stmt(st);
        }   

        m_output << "    mov rax, 60\n";
        m_output << "    mov rdi, 0\n";
        m_output << "    syscall";
        return m_output.str();
    }

private:
    const NodeProg m_prog;
    std::stringstream m_output;
};