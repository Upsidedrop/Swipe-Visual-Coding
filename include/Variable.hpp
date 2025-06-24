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
    void setPos(Vector2f p_pos) override{
        pos = p_pos;

        float a = (currentFrame.x + currentFrame.w) * scale.x;
        float b = text.getDimensions().x + currentFrame.w * scale.x;

        middle -> setPos(Vector2f(a + p_pos.x, p_pos.y));
        end -> setPos(Vector2f(((a < b) ? b : a) + p_pos.x, p_pos.y));
    }
    private:
    Collider* collision;
    Gap* parent;
    Entity* middle;
    Entity* end;
    TextBox text;
};