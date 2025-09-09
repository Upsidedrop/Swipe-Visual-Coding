#pragma once

#include <unordered_map>
#include <string>

#include "Block.hpp"

class FuncHead;

extern std::unordered_map<std::string, FuncHead*> functions;

class FuncHead : public Block{
    public:
    FuncHead(Vector2f p_pos, float p_scale, SDL_Texture* p_tex, BlockType p_type, SDL_Rect p_frame, std::string p_name, Vector2f p_textOffset = Vector2f(10, 20), std::vector<const char*> p_parameters = {});
    void setPos(Vector2f p_pos) override
    {
        pos = p_pos;
        //currentFrame > -2 < is to account for dip at bottom of block and top of other block
        if(child != nullptr)
        {
            SDL_Rect foo = parts.bottomLeft->getCurrentFrame();
            child-> setPos(p_pos + Vector2f(0, (foo.y + foo.h - 2) * scale.y));
        }
        text.getVisual() -> setPos(p_pos + textOffset); 
        
        parts.top -> setPos(Vector2f(p_pos.x + currentFrame.w * scale.x, p_pos.y));
        parts.topRight -> setPos(Vector2f(p_pos.x + currentFrame.w * scale.x + parts.top -> getCurrentFrame().w * parts.top->getScale().x, p_pos.y));
        
        Vector2f topMargin(0, parts.left->getCurrentFrame().y * scale.y);

        parts.left -> setPos(p_pos + topMargin);
        parts.center -> setPos(parts.top -> getPos() + topMargin);
        parts.right -> setPos(parts.topRight -> getPos() + topMargin);

        topMargin.y = parts.bottomLeft->getCurrentFrame().y * scale.y;

        parts.bottomLeft -> setPos(p_pos + topMargin);
        parts.bottom -> setPos(parts.top -> getPos() + topMargin);
        parts.bottomRight -> setPos(parts.topRight -> getPos() + topMargin);
        
        MoveParameters(p_pos);
    }
};