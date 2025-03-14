#pragma once

#include "Entity.hpp"
#include "Block.hpp"
#include "Math.hpp"

class Loop : Block{
    public:
    Loop(Vector2f p_pos, Vector2f p_scale, SDL_Texture* p_tex, std::map<int, std::unordered_set<Entity*>>* p_layers, vector<vector<Collider*>>* colliderFlags, SDL_Rect p_frame);
    ~Loop();
    private:
    Entity* body;
    Entity* foot;
};