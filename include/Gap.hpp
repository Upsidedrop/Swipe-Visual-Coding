#pragma once

#include "Entity.hpp"
#include "Math.hpp"
#include "Variable.hpp"

extern SDL_Texture* gapTexture;

class Gap : public Entity{
    public:
    Gap(Vector2f p_pos, Vector2f p_scale = Vector2f(4,4), int p_layer = 0);
    ~Gap();
    float GetSize();
    private:
    Variable* attached;
    Collider* col;
};