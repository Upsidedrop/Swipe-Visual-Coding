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
        void render(Entity& p_entity, RenderType p_renderType);
        void display();
        void changeBackground(SDL_Color p_color);
        void windowResized(int p_width, int p_height);
        void renderSideBar();
    private:
        SDL_Rect frameObject(Entity& p_entity);
        SDL_Rect frameUI(Entity& p_entity);
        SDL_Window* window;
        SDL_Renderer* renderer;
        int width, height;
};
