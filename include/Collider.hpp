#pragma once

#include <iostream>
#include <SDL.h>
#include <vector>
#include <functional>

#include "Entity.hpp"

class Collider;

extern std::vector<std::vector<Collider*>> flags;

class Collider{
public:
    enum FLAG{
        TOP_BLOCK,
        BOTTOM_BLOCK,
        GRABBABLE,
        BUTTON,
        GRABBABLE_VAR,
        GAP,
        TEXT_AREA
    };
    Collider()
    :frame(SDL_FRect()), parent(nullptr){}
    Collider(SDL_FRect p_frame, Entity* p_parent, FLAG p_layer) 
    :frame(p_frame),  parent(p_parent){
        flags[p_layer].push_back(this);
    }
    SDL_FRect GetFrame(){
        return frame;
    }
    void SetFrame(SDL_FRect p_frame){
        frame = p_frame;
    }
    Entity* GetParent(){
        return parent;
    }
    Collider* CheckForCollisions(std::vector<int> masks, std::function<bool(Collider*)> p_predicate = [](Collider*) -> bool {return false;});
    Collider* CheckForCollisionsHeightPriority(std::vector<int> masks);
    float getArea();
    private:
    SDL_FRect frame;
    Entity* parent;
};
