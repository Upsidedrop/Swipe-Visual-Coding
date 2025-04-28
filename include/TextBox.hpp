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
    TextBox(const char* p_text, Vector2f p_pos, SDL_Color p_color = {255, 255, 255});
    ~TextBox();
    private:
    Entity* visual;
    SDL_Surface* surface;
    SDL_Texture* tex;
};