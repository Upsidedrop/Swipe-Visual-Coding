#pragma once

#include <unordered_map>
#include <string>

#include "Block.hpp"

class FuncHead;

extern std::unordered_map<std::string, FuncHead*> functions;

class FuncHead : public Block{
    public:
    FuncHead(Vector2f p_pos, Vector2f p_scale, SDL_Texture* p_tex, BlockType p_type, SDL_Rect p_frame, std::string p_name);
    void setPos(Vector2f p_pos) override
    {
        pos = p_pos;
        if(child != nullptr)
        {
            child-> setPos(p_pos + Vector2f(0, 13 * scale.y));
        }
    }
};