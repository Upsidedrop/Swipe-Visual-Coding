#pragma once

#include "Entity.hpp"
#include "Math.hpp"

extern SDL_Texture* gapTexture;

class Gap{
    public:
    Gap(Vector2f p_pos);
    private:
    Entity* body;
};