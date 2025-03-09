#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <map>
#include <unordered_set>

#include "Math.hpp"

class Entity{
    public:
    Entity(Vector2f p_pos, SDL_Texture* p_tex, std::map<int, std::unordered_set<Entity*>>* p_layers, SDL_Rect p_frame, Vector2f p_scale = Vector2f(1,1), int p_layer = 0);
    Vector2f& getPos()
    {
        return pos;
    }
    virtual void setPos(Vector2f p_pos){
        pos = p_pos;
    }
    void setScale(Vector2f p_scale){
        scale = p_scale;
    }
    Vector2f& getScale(){
        return scale;
    }
    virtual void SetLayer(int p_layer);
    SDL_Texture* getTex();
    SDL_Rect getCurrentFrame();
    virtual ~Entity(){}
    protected:
    int layer = 0;
    std::map<int, std::unordered_set<Entity*>>* layers;
    Vector2f pos;
    Vector2f scale;
    SDL_Rect currentFrame;
    SDL_Texture* tex;
};