#include "FuncHead.hpp"

FuncHead::FuncHead(Vector2f p_pos, float p_scale, SDL_Texture* p_tex, BlockType p_type , SDL_Rect p_frame, std::string p_name, Vector2f p_textOffset)
:Block(p_pos, p_tex, p_frame, p_type, p_scale, p_name.c_str(), p_textOffset){

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

    float a = (p_frame.x + p_frame.w) * p_scale;
    float b = text.getDimensions().x + p_textOffset.x * 2;

    middle = (a < b) ? new Entity(Vector2f(a + p_pos.x, p_pos.y), p_tex, middleSize, Vector2f((b - a) / middleSize.w, p_scale)) : nullptr;

    end = new Entity(Vector2f(((a < b) ? b : a) + p_pos.x, p_pos.y), p_tex, endSize, Vector2f(p_scale, p_scale));
}