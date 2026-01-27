#pragma once

#include <SDL.h>
#include <unordered_map>

#include "Collider.hpp"
#include "Math.hpp"
#include "FuncHead.hpp"

extern std::unordered_map<std::string, FuncHead*> functions;
extern std::map<int, RandomDeletionStack<Entity*>*> layers;

namespace utils{
    Collider* CheckMouseCollisions(Vector2f p_mousePos, vector<int> p_masks);
    void DeconstructFunctionHeads();
    void DeconstructLayers();
    SDL_FRect RectToFrect(SDL_Rect& p_rect);
    SDL_Rect InitRect(int x, int y, int w, int h);
}
