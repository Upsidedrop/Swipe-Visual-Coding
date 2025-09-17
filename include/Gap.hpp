#pragma once

#include "Entity.hpp"
#include "Math.hpp"
#include "Variable.hpp"
#include "HeightChanger.hpp"

class Block;

extern SDL_Texture* gapTexture;

class Gap : public Entity{
    public:
    Gap(Vector2f p_pos, HeightChanger& p_heightChanger, void* p_identity, bool p_isBlock, Vector2f p_scale = Vector2f(4,4), int p_layer = 0);
    ~Gap();
    float GetSize();
    float GetHeight();
    void SetAttached(Variable* p_attached);
    void setPos(Vector2f p_pos) override;
    void SetLayer(int p_layer) override;
    void Detach();
    private:
    Variable* attached;
    Collider* col;
    HeightChanger& heightChanger;
    void* identity;
    bool isBlock;
};