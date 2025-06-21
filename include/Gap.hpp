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
    void SetAttached(Variable* p_attached);
    void setPos(Vector2f p_pos) override {
        pos = p_pos;
        if(attached != nullptr){
            attached -> setPos(p_pos);
        }
    }
    private:
    Variable* attached;
    Collider* col;
};