#pragma once

#include <SDL.h>
#include <SDL_ttf.h>
#include <SDL_image.h>

#include "Math.hpp"
#include "Entity.hpp"
#include "RenderWindow.hpp"

extern RenderWindow window;
extern TTF_Font* comic;

class TextBox{
    public:
    TextBox(const char* p_text, Vector2f p_pos, float p_scale = 1, int p_layer = 0, SDL_Color p_color = {0, 0, 0});
    ~TextBox();
    Entity* getVisual(){
        return visual;
    }
    Vector2f getDimensions(){
        return Vector2f(visual -> getCurrentFrame().w, visual -> getCurrentFrame().h) * scale;
    }
    void setText(const char* p_text);
    float getScale();
    private:
    void updateTextures(const char* p_text);
    void deleteTextures();
    SDL_Rect getFrame();
    Entity* visual;
    SDL_Surface* surface;
    SDL_Texture* tex;
    float scale;
    SDL_Color color;
};
