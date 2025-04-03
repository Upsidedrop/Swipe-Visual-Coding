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

    void Compile(){
        program.open(prefPath + "program.cpp");
        Block* it;
        it = functions["main"];
        program << "#include <iostream> \nint main(){";
        while(it != nullptr){
            if(it -> GetType() == BlockType::DEFAULT){
                program << "std::cout << \"Hello World!\\n\";";
            }
            it = it -> getChild(); 
        }
        program << "}";

        program.close();

        std::string command = "cd " + prefPath + " && g++ program.cpp -Wall && ./a.out";

        system(command.c_str());
    }
}