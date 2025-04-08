#pragma once

#include <unordered_map>
#include <string>
#include <iostream>
#include <fstream>

#include "FuncHead.hpp"
#include "Block.hpp"

extern std::unordered_map<std::string, FuncHead*> functions;

namespace Compilation{
    std::string prefPath = SDL_GetPrefPath("Oddity", "Swipe");
    std::ofstream program;

    void TypeChecker(Block* it, char foo){
        if(it == nullptr){
            return;
        }
        if(it -> GetType() == BlockType::DEFAULT){
            program << "std::cout << \"Hello World!\\n\";";
        }
        if(it -> GetType() == BlockType::DEFAULTLOOP){
            program << "for(int " << foo << " =0;" << foo << "<3;++" << foo <<"){";
            TypeChecker(((Loop*)(it)) -> GetInnerChild(), foo + 1);
            program << "}";
        }
        TypeChecker(it -> getChild(), foo);
    }
    
    void Compile(){
        program.open(prefPath + "program.cpp");

        program << "#include <iostream> \nint main(){";

        TypeChecker(functions["main"], 'a');

        program << "}";

        program.close();

        std::string command = "cd " + prefPath + " && g++ program.cpp -Wall && ./a.out";

        system(command.c_str());
    }
}