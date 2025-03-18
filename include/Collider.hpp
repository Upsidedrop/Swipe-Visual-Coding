#pragma once

#include <iostream>
#include <SDL2/SDL.h>
#include <vector>

class Block;

class Collider{
public:
    Collider()
    :frame(SDL_FRect()), parent(nullptr){}
    Collider(SDL_FRect p_frame, Block* p_parent, std::vector<std::vector<Collider*>>* p_flags, int p_layer) 
    :frame(p_frame), flags(p_flags), parent(p_parent){
        ((p_flags -> data()) + p_layer) -> push_back(this);
    }
    SDL_FRect GetFrame(){
        return frame;
    }
    void SetFrame(SDL_FRect p_frame){
        frame = p_frame;
    }
    Block* GetParent(){
        return parent;
    }
    Collider* CheckForCollisions(std::vector<int> masks);
private:
    SDL_FRect frame;
    std::vector<std::vector<Collider*>>* flags;
    Block* parent;
};