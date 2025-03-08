#pragma once

#include <SDL2/SDL.h>

#include "Collider.hpp"
#include "Math.hpp"

namespace utils{
    inline float hireTimeInSeconds(){
        float t = SDL_GetTicks64();
        t *= 0.001f;

        return t;
    }
    Collider* CheckMouseCollisions(Vector2f p_mousePos, vector<vector<Collider*>>* p_flags, vector<int> p_masks){
        for(int i : p_masks){
            for(Collider* other : *(p_flags -> data() + i)){
                if((other -> GetParent() -> getPos().x + (other -> GetFrame().w + other -> GetFrame().x) * other->GetParent()->getScale().x) < p_mousePos.x){
                    continue;
                }
                if((other -> GetParent() -> getPos().y + (other -> GetFrame().h + other -> GetFrame().y) * other->GetParent()->getScale().y) < p_mousePos.y){
                    continue;
                }
                if(p_mousePos.x < (other -> GetParent() -> getPos().x) + other -> GetFrame().x){
                    continue;
                }
                if(p_mousePos.y < (other -> GetParent() -> getPos().y) + other -> GetFrame().y){
                    continue;
                }
                return other;
            }
        }
        return nullptr;
    }
}