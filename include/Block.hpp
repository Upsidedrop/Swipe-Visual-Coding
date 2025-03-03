#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <vector>

#include "Math.hpp"
#include "Collider.hpp"
#include "Entity.hpp"

using namespace std;

class Block : public Entity{
    public:
    Block(Vector2f p_pos, SDL_Texture* p_tex, vector<vector<Collider*>>* colliderFlags, Vector2f p_scale = Vector2f(1,1), uint p_w = 32, uint p_h = 32);
    Collider& getBottomCollider(){
        return bottomCollider;
    }
    Collider& getTopCollider(){
        return topCollider;
    }
    Block* getChild(){
        return child;
    }
    void setChild(Block* p_child){
        child = p_child;
    }
    private:
    Collider bottomCollider;
    Collider topCollider;
    Block* child;
};