#include "FuncHead.hpp"

FuncHead::FuncHead(Vector2f p_pos, float p_scale, SDL_Texture* p_tex, BlockType p_type , SDL_Rect p_frame, std::string p_name, Vector2f p_textOffset, std::vector<const char*> p_parameters)
:Block(p_pos, p_tex, p_frame, p_type, p_scale, p_name.c_str(), p_textOffset, p_parameters){

    SDL_FRect bottomColRect;
    bottomColRect = bottomCollider->GetFrame();
    bottomColRect.y += 3;
    bottomCollider -> SetFrame(bottomColRect);

    functions[p_name] = this;

    SDL_Rect middleSize;
    middleSize.x = p_frame.w;
    middleSize.y = 0;
    middleSize.w = 29;
    middleSize.h = p_frame.h;

    SDL_Rect endSize;
    endSize.x = middleSize.x + middleSize.w;
    endSize.y = 0;
    endSize.w = 15;
    endSize.h = p_frame.h;

    BlockResize::InitBlockScale(
        p_frame, middleSize, endSize,
        p_scale, text, p_textOffset, 
        parameters, p_pos, parameterOffsets, 
        p_tex, p_parameters, this, 
        middle, end
    );
    for(auto pair : parameters){
        pair.first -> getVisual() -> SetLayer(layer + 1);
        pair.second -> SetLayer(layer + 1);
    }

    SDL_FRect mainColFrame;
    mainColFrame.x = 0;
    mainColFrame.y = 0;
    mainColFrame.w = currentFrame.w + ((middle != nullptr)? middleSize.w * middle -> getScale().x / p_scale : 0) + endSize.w;
    mainColFrame.h = currentFrame.h;

    mainCollider = new Collider(mainColFrame, this, 2);
}