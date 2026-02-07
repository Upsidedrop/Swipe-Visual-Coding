#pragma once

#include <unordered_map>
#include <string>
#include <iostream>
#include <fstream>

#include "FuncHead.hpp"
#include "Block.hpp"

extern std::unordered_map<std::string, FuncHead*> functions;

namespace Compilation{
    void TypeChecker(Block* it, char foo);
    void Compile();
    void GetVarVal(Variable* p_var, std::string& p_line);
}