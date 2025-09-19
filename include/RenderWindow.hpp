#pragma once
#include <SDL.h>
#include <SDL_image.h>

#include "Entity.hpp"

class RenderWindow{
    public:
        RenderWindow(const char* p_title, int p_w, int p_h);
        SDL_Texture* loadTexture(const char* p_filePath);
        SDL_Texture* loadSurface(SDL_Surface* surface);
        void cleanUp();
        void clear();
        void render(Entity& p_entity);
        void display();
        void changeBackground(SDL_Color p_color);
    private:
        SDL_Window* window;
        SDL_Renderer* renderer;
};
