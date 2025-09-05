#include "FuncHead.hpp"

FuncHead::FuncHead(Vector2f p_pos, float p_scale, SDL_Texture* p_tex, BlockType p_type , SDL_Rect p_frame, std::string p_name, Vector2f p_textOffset, std::vector<const char*> p_parameters)
:Block(p_pos, p_tex, p_frame, p_type, p_scale, p_name.c_str(), p_textOffset, p_parameters){    
    parts.limits.y = 17;

    SDL_FRect bottomColRect;
    bottomColRect = bottomCollider->GetFrame();
    bottomColRect.y += 3;
    bottomCollider -> SetFrame(bottomColRect);

    functions[p_name] = this;

    SDL_Rect centerSize;
    centerSize.x = 27;
    centerSize.y = 4;
    centerSize.w = 25;
    centerSize.h = 11;

    BlockResize::InitBlockScale(
        centerSize, parts, p_scale, text, p_textOffset, parameters, p_pos, parameterOffsets, p_tex, p_parameters, heightChanger
    );
    for(auto pair : parameters){
        pair.first -> getVisual() -> SetLayer(layer + 1);
        pair.second -> SetLayer(layer + 1);
    }

    mainCollider = parts.GenerateGrabbableCollider(this);
}