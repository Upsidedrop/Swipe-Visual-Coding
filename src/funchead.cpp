#include "FuncHead.hpp"

FuncHead::FuncHead(Vector2f p_pos, float p_scale, SDL_Texture* p_tex, BlockType p_type , SDL_Rect p_frame, std::string p_name)
:Block(p_pos, p_tex, p_frame, p_type, p_scale)
{
    delete topCollider;
    topCollider = nullptr;
    
    SDL_FRect bottomColRect;
    bottomColRect = bottomCollider->GetFrame();
    bottomColRect.y += 2;
    bottomCollider -> SetFrame(bottomColRect);

    functions[p_name] = this;
}
