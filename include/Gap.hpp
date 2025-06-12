#pragma once

#include "Entity.hpp"
#include "Math.hpp"

extern SDL_Texture* gapTexture;

class Gap{
    public:
    Gap(Vector2f p_pos);
    ~Gap();
    float GetSize();
    void setPos(Vector2f p_pos){
        body -> setPos(p_pos);
    }
    private:
    Entity* body;
};