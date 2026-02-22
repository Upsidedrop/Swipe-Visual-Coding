#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include <map>

#include "Math.hpp"
#include "RandomDeletionStack.hpp"

class Entity;

extern std::map<int, RandomDeletionStack<Entity*>*> layers;

enum RenderType{
    OBJECT,
    UI
};

class Entity{
    public:
    Entity(Vector2f p_pos, SDL_Texture* p_tex, SDL_Rect p_frame, Vector2f p_scale = Vector2f(1,1), int p_layer = 0, RenderType p_renderType = OBJECT);
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
    void setTex(SDL_Texture* p_tex);
    void setFrame(SDL_Rect p_frame);
    virtual void SetLayer(int p_layer);
    SDL_Texture* getTex();
    SDL_Rect getCurrentFrame();
    virtual ~Entity(){}
    void SetSelfLayer(int p_layer);
    bool enabled;
    RenderType getRenderType();
    protected:
    int layer = 0;
    Vector2f pos;
    Vector2f scale;
    SDL_Rect currentFrame;
    SDL_Texture* tex;
    RenderType renderType;
};
