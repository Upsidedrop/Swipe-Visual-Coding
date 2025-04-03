#pragma once

#include <SDL2/SDL.h>
#include <unordered_map>

#include "Collider.hpp"
#include "Math.hpp"
#include "FuncHead.hpp"

extern std::unordered_map<std::string, FuncHead*> functions;

namespace utils{
    inline float hireTimeInSeconds(){
        float t = SDL_GetTicks64();
        t *= 0.001f;

        return t;
    }
    Collider* CheckMouseCollisions(Vector2f p_mousePos, vector<int> p_masks){
        for(int i : p_masks){
            for(Collider* other : flags[i]){
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
    void DeconstructFunctionHeads(){
        for(auto functionHeadPair : functions){
            delete functionHeadPair.second;
        }
    }
}