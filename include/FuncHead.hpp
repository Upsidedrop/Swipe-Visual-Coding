#pragma once

#include "Block.hpp"

class FuncHead : Block{
    public:
    FuncHead(Vector2f p_pos, Vector2f p_scale, SDL_Texture* p_tex, BlockType p_type , SDL_Rect p_frame);
    void setPos(Vector2f p_pos) override
    {
        pos = p_pos;
        if(child != nullptr)
        {
            child-> setPos(p_pos + Vector2f(0, 13 * scale.y));
        }
    }
};