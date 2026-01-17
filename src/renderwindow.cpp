#include <SDL.h>
#include <SDL_image.h>
#include <iostream>

#include "RenderWindow.hpp"
#include "Entity.hpp"

extern Vector2f cameraPos;

RenderWindow::RenderWindow(const char* p_title, int p_w, int p_h) :window(nullptr), renderer(nullptr) {
    window = SDL_CreateWindow(p_title, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, p_w, p_h, SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);
    if(window == nullptr){
        std::cout << "WINDOW FAILED TO INIT. ERROR: " << SDL_GetError() << std::endl; 
    }
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
}
SDL_Texture* RenderWindow::loadTexture(const char* p_filePath){
    SDL_Texture* texture = nullptr;
    texture = IMG_LoadTexture(renderer, p_filePath);
    if(texture == nullptr){
        std::cout << "FAILED TO LOAD TEXTURE. ERROR: " << SDL_GetError() << std::endl;
    }
    return texture;
}
SDL_Texture* RenderWindow::loadSurface(SDL_Surface* surface){
    SDL_Texture* texture = nullptr;
    texture = SDL_CreateTextureFromSurface(renderer, surface);
    if(texture == nullptr){
        std::cout << "FAILED TO LOAD TEXTURE. ERROR: " << SDL_GetError() << std::endl;
    }
    return texture;
}
void RenderWindow::cleanUp(){
    SDL_DestroyWindow(window);
}
void RenderWindow::clear(){
    SDL_RenderClear(renderer);
}
void RenderWindow::render(Entity& p_entity){
    SDL_Rect src;
    src.x = p_entity.getCurrentFrame().x;
    src.y = p_entity.getCurrentFrame().y;
    src.w = p_entity.getCurrentFrame().w;
    src.h = p_entity.getCurrentFrame().h;

    SDL_Rect dst;
    dst.x = p_entity.getPos().x - cameraPos.x;
    dst.y = p_entity.getPos().y - cameraPos.y;
    dst.w = p_entity.getCurrentFrame().w * p_entity.getScale().x;
    dst.h = p_entity.getCurrentFrame().h * p_entity.getScale().y;
    SDL_RenderCopy(renderer, p_entity.getTex(), &src, &dst);
}
void RenderWindow::display(){
    SDL_RenderPresent(renderer);
}
void RenderWindow::changeBackground(SDL_Color p_color){
    SDL_SetRenderDrawColor(renderer, p_color.r, p_color.g, p_color.b, p_color.a);
}