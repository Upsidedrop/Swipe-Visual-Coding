#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>

#include "Math.hpp"
#include "Entity.hpp"
#include "RenderWindow.hpp"

extern RenderWindow window;
extern TTF_Font* comic;

class TextBox{
    public:
    TextBox(const char* p_text, Vector2f p_pos, float p_scale = 1, int p_layer = 1, SDL_Color p_color = {0, 0, 0});
    ~TextBox();
    Entity* getVisual(){
        return visual;
    }
    Vector2f getDimensions(){
        return Vector2f(visual -> getCurrentFrame().w, visual -> getCurrentFrame().h) * scale;
    }
    float getScale();
    private:
    Entity* visual;
    SDL_Surface* surface;
    SDL_Texture* tex;
    float scale;
};