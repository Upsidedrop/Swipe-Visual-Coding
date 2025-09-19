#pragma once

#include <SDL.h>
#include <unordered_map>

#include "Collider.hpp"
#include "Math.hpp"
#include "FuncHead.hpp"

extern std::unordered_map<std::string, FuncHead*> functions;

namespace utils{
    inline float hireTimeInSeconds(){
        float t = SDL_GetTicks64();
        t *= 0.001f;

        return t;
    }
    Collider* CheckMouseCollisions(Vector2f p_mousePos, vector<int> p_masks);
    void DeconstructFunctionHeads();
    SDL_FRect RectToFrect(SDL_Rect& p_rect);
    SDL_Rect InitRect(int x, int y, int w, int h);
}