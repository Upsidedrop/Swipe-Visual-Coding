#include "Compiler.hpp"
#include "Loop.hpp"

namespace Compilation{
    std::string prefPath = SDL_GetPrefPath("Oddity", "Swipe");
    std::ofstream program;
    
    void TypeChecker(Block* it, char foo){
        if(it == nullptr){
            return;
        }
        if(it -> getSnippet() == CodeSnippet::PRINT){
            auto message = it -> getParam(0) -> getAttached() -> getText();
            program << "std::cout << \""<< message << "\\n\";\n";
            
        }
        if(it -> GetType() == BlockType::DEFAULTLOOP){
            program << "for(int " << foo << " =0;" << foo << "<3;++" << foo <<"){\n";
            TypeChecker(((Loop*)(it)) -> GetInnerChild(), foo + 1);
            program << "}\n";
        }
        TypeChecker(it -> getChild(), foo);
    }

    void Compile(){
        program.open(prefPath + "program.cpp");

        program << "#include <iostream> \nint main(){\n";

        TypeChecker(functions["main"], 'a');

        program << "}";

        program.close();

        std::string command = "cd " + prefPath + " && g++ program.cpp -Wall && ./a.out";

        system(command.c_str());
    }
}
