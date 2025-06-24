#pragma once

#include <SDL2/SDL_image.h>

#include "Collider.hpp"

class Gap;

class Variable : public Entity{
    public:
    Variable(Vector2f p_pos, SDL_Texture* p_tex, Vector2f p_scale = Vector2f(1,1), int p_layer = 0);
    ~Variable();
    Collider* GetCollider();
    void SetParent(Gap* p_parent);
    Gap* GetParent();
    private:
    Collider* collision;
    Gap* parent;
};