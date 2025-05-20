#pragma once

#include <iostream>
#include <SDL2/SDL.h>
#include <vector>

#include "Entity.hpp"

class Collider;

extern std::vector<std::vector<Collider*>> flags;

class Collider{
public:
    Collider()
    :frame(SDL_FRect()), parent(nullptr){}
    Collider(SDL_FRect p_frame, Entity* p_parent, int p_layer) 
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
    Collider* CheckForCollisions(std::vector<int> masks);
    Collider* CheckForCollisionsHeightPriority(std::vector<int> masks);
    private:
    SDL_FRect frame;
    Entity* parent;
};