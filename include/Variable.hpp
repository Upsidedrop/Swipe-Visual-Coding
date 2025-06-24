#pragma once

#include <SDL2/SDL_image.h>

#include "Collider.hpp"
#include "TextBox.hpp"

class Gap;

class Variable : public Entity{
    public:
    Variable(Vector2f p_pos, SDL_Texture* p_tex, const char *p_text, float p_scale = 4, int p_layer = 0);
    ~Variable();
    Collider* GetCollider();
    void SetParent(Gap* p_parent);
    Gap* GetParent();
    private:
    Collider* collision;
    Gap* parent;
    Entity* middle;
    Entity* end;
    TextBox text;
};