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
            SDL_Rect foo = bottomLeft->getCurrentFrame();
            child-> setPos(p_pos + Vector2f(0, (foo.y + foo.h - 2) * scale.y));
        }
        text.getVisual() -> setPos(p_pos + textOffset); 
        
        top -> setPos(Vector2f(p_pos.x + currentFrame.w * scale.x, p_pos.y));
        topRight -> setPos(Vector2f(p_pos.x + currentFrame.w * scale.x + top -> getCurrentFrame().w * top->getScale().x, p_pos.y));
        
        Vector2f topMargin(0, left->getCurrentFrame().y * scale.y);

        left -> setPos(p_pos + topMargin);
        center -> setPos(top -> getPos() + topMargin);
        right -> setPos(topRight -> getPos() + topMargin);

        topMargin.y = bottomLeft->getCurrentFrame().y * scale.y;

        bottomLeft -> setPos(p_pos + topMargin);
        bottom -> setPos(top -> getPos() + topMargin);
        bottomRight -> setPos(topRight -> getPos() + topMargin);
    
        for(size_t i = 0; i < parameters.size(); ++i){
            parameters[i].first -> getVisual() -> setPos(parameterOffsets[i].first + p_pos);

            parameters[i].second -> setPos(parameterOffsets[i].second + p_pos);
        }
    }
};