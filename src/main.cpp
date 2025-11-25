#include "./code_gen.hpp"

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

    Parser parser(tokens);
    std::optional<NodeProg> node = parser.parse_prog();

    if(!node){
        std::cerr<<"INvalid program"<<std::endl;
        exit(EXIT_FAILURE);
    }

    Generator gen(node.value());
    {
        std::fstream asm_file(std::filesystem::path("./out.asm").string(), std::ios::out);
        asm_file << gen.gen_code();
    }

    system("nasm -felf64 out.asm");
    system("ld -o out out.o");

    return EXIT_SUCCESS;
}
