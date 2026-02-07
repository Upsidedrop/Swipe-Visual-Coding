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
            bool isString = it -> getParam(0) -> getAttached() -> hasText();

            std::string thisLine = "std::cout << ";
            if(isString){
                thisLine.push_back('\"');
            }
            GetVarVal(it -> getParam(0) -> getAttached(), thisLine);
            if(isString){
                thisLine.push_back('\"');
            }
            program << thisLine << " << \"\\n\";\n";
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
    void GetVarVal(Variable* p_var, std::string& p_line){
        if(p_var -> hasText()){
            p_line += p_var -> getText();
            return;
        }
        if(p_var -> getCommand() == VarCommand::ADD){
            p_line += "(";
            GetVarVal(p_var -> getParam(0) -> getAttached(), p_line);
            p_line += " + ";
            GetVarVal(p_var -> getParam(1) -> getAttached(), p_line);
            p_line += ")";
            return;
        }
    }
}
