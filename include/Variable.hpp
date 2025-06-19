#pragma once

#include <SDL2/SDL_image.h>

#include "Collider.hpp"

class Variable : Entity{
    public:
    Variable(Vector2f p_pos, SDL_Texture* p_tex, SDL_Rect p_frame, Vector2f p_scale = Vector2f(1,1), int p_layer = 0);
    ~Variable();
    private:
    Collider* collision;
};