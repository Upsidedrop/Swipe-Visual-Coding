#pragma once

#include "Entity.hpp"

struct DividedEntity{
    Entity* top;
    Entity* topRight;
    Entity* left;
    Entity* center;
    Entity* right;
    Entity* bottomLeft;
    Entity* bottom;
    Entity* bottomRight;
    ~DividedEntity(){
        delete top;
        delete topRight;
        delete left;
        delete center;
        delete right;
        delete bottomLeft;
        delete bottom;
        delete bottomRight;
    }
};