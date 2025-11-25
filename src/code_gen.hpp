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
                gen->push("rax");
            }
            void operator()( const NodeExprIdent& expr_ident){
                // if we do let x = 0; let y = x or something like that
                if(gen->m_vars.find(expr_ident.ident.value.value()) == gen->m_vars.end()){
                    std::cerr<<"undeclared indentifire: "<<expr_ident.ident.value.value()<<std::endl;
                    exit(EXIT_FAILURE);
                }

                const auto& var = gen->m_vars.at(expr_ident.ident.value.value());
                // offset from stack pointer x86
                gen->push("QWORD [rsp + " + std::to_string((gen->m_stack_size - var.stack_loc) * 8) + "]");
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
                gen->pop("rdi");
                gen->m_output << "    syscall\n";
            }
            void operator()(const NodeStatementManlo& stmt_manloo){ //2>
                if(gen->m_vars.find(stmt_manloo.ident.value.value()) != gen->m_vars.end()){
                    std::cerr<<"Variable named already used: "<<stmt_manloo.ident.value.value() <<std::endl;;
                    exit(EXIT_FAILURE);
                }
                
                gen->m_vars.insert({stmt_manloo.ident.value.value(), Var {.stack_loc = gen->m_stack_size}});
                gen->gen_expr(stmt_manloo.expr); // now the value of the expr is top of the stck 
            }
        };

        StmtVisitor visitor {.gen = this};
        std::visit(visitor, stmt.var); // it will call the exit the 1 oand if manlo then call 2
    }

    [[nodiscard]] std::string gen_code(){
        m_output << "global _start:\n_start:\n";
        
        // TODO: only one variable is being initialized. Debug it
        for(const NodeStatements& st: m_prog.stmts){
            gen_stmt(st);
        }   

        m_output << "    mov rax, 60\n";
        m_output << "    mov rdi, 0\n";
        m_output << "    syscall";
        return m_output.str();
    }

private:

    void push(const std::string& reg){
        m_output << "    push "<< reg<<"\n";
        m_stack_size++;
    }

    void pop(const std::string& reg){
        m_output << "    pop "<<reg<<"\n";
        m_stack_size--;
    }

    struct Var{
        size_t stack_loc;
        // todo: add type
    };

    const NodeProg m_prog;
    std::stringstream m_output;
    size_t m_stack_size = 0;
    std::unordered_map<std::string, Var> m_vars {};
};