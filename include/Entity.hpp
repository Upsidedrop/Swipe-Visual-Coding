#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "Math.hpp"

class Entity{
    public:
    Entity(Vector2f p_pos, SDL_Texture* p_tex, Vector2f p_scale = Vector2f(1,1), uint p_w = 32, uint p_h = 32);
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
    SDL_Texture* getTex();
    SDL_Rect getCurrentFrame();
    
    protected:
    Vector2f pos;
    SDL_Rect currentFrame;
    Vector2f scale;
    SDL_Texture* tex;
};