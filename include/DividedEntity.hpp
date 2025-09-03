#pragma once

#include "Entity.hpp"
#include "Math.hpp"

class DividedEntity{
    public:
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
    void SetPos(Vector2f& p_pos);
};