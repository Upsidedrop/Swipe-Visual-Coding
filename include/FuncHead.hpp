#pragma once

#include <unordered_map>
#include <string>

#include "Block.hpp"

class FuncHead;

extern std::unordered_map<std::string, FuncHead*> functions;

class FuncHead : public Block{
    public:
    FuncHead(Vector2f p_pos, float p_scale, SDL_Texture* p_tex, BlockType p_type, SDL_Rect p_frame, std::string p_name);
    void setPos(Vector2f p_pos) override
    {
        pos = p_pos;
        if(child != nullptr)
        {
            child-> setPos(p_pos + Vector2f(0, 13 * scale.y));
        }
        text.getVisual() -> setPos(p_pos + Vector2f(10, 5));
        middle -> setPos(Vector2f(p_pos.x + 13 * scale.x, p_pos.y));
        end -> setPos(Vector2f(p_pos.x + 13 * scale.x + text.getDimensions().x, p_pos.y));
    }
};