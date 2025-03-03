#pragma once

#include <SDL2/SDL.h>
#include <vector>

using namespace std;

class Block;

class Collider{
public:
    Collider()
    :frame(SDL_FRect()), parent(nullptr){}
    Collider(SDL_FRect p_frame, Block* p_parent, vector<vector<Collider*>>* p_flags) 
    :frame(p_frame), flags(p_flags), parent(p_parent){}
    SDL_FRect& GetFrame(){
        return frame;
    }
    Block* GetParent(){
        return parent;
    }
    Collider* CheckForCollisions(vector<int> masks);
private:
    SDL_FRect frame;
    vector<vector<Collider*>>* flags;
    Block* parent;
};