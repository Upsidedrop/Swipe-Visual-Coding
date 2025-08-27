#include "FuncHead.hpp"

FuncHead::FuncHead(Vector2f p_pos, float p_scale, SDL_Texture* p_tex, BlockType p_type , SDL_Rect p_frame, std::string p_name, Vector2f p_textOffset, std::vector<const char*> p_parameters)
:Block(p_pos, p_tex, p_frame, p_type, p_scale, p_name.c_str(), p_textOffset, p_parameters){

    SDL_FRect bottomColRect;
    bottomColRect = bottomCollider->GetFrame();
    bottomColRect.y += 3;
    bottomCollider -> SetFrame(bottomColRect);

    functions[p_name] = this;

    SDL_Rect topSize;
    topSize.x = p_frame.w;
    topSize.y = 0;
    topSize.w = 51 - p_frame.w;
    topSize.h = p_frame.h;

    SDL_Rect topRightSize;
    topRightSize.x = topSize.x + topSize.w;
    topRightSize.y = 0;
    topRightSize.w = 65 - topRightSize.x;
    topRightSize.h = p_frame.h;

    SDL_Rect leftSize;
    leftSize.x = 0;
    leftSize.y = p_frame.h;
    leftSize.w = p_frame.w;
    leftSize.h = 14 - p_frame.h;

    SDL_Rect centerSize;
    centerSize.x = topSize.x;
    centerSize.y = leftSize.y;
    centerSize.w = topSize.w;
    centerSize.h = leftSize.h;

    SDL_Rect rightSize;
    rightSize.x = topRightSize.x;
    rightSize.y = leftSize.y;
    rightSize.w = topRightSize.w;
    rightSize.h = leftSize.h;

    SDL_Rect bottomLeftSize;
    bottomLeftSize.x = 0;
    bottomLeftSize.y = leftSize.y + leftSize.h;
    bottomLeftSize.w = p_frame.w;
    bottomLeftSize.h = 17 - bottomLeftSize.y;

    SDL_Rect bottomSize;
    bottomSize.x = topSize.x;
    bottomSize.y = bottomLeftSize.y;
    bottomSize.w = topSize.w;
    bottomSize.h = bottomLeftSize.h;

    SDL_Rect bottomRightSize;
    bottomRightSize.x = topRightSize.x;
    bottomRightSize.y = bottomLeftSize.y;
    bottomRightSize.w = topRightSize.w;
    bottomRightSize.h = bottomLeftSize.h;

    BlockResize::InitBlockScale(
        p_frame, topSize, topRightSize, leftSize, centerSize,
        rightSize, bottomLeftSize, bottomSize, bottomRightSize,
        parts, p_scale,
        text, p_textOffset, parameters, p_pos, parameterOffsets, p_tex,
        p_parameters, this
    );
    for(auto pair : parameters){
        pair.first -> getVisual() -> SetLayer(layer + 1);
        pair.second -> SetLayer(layer + 1);
    }

    SDL_FRect mainColFrame;
    mainColFrame.x = 0;
    mainColFrame.y = 0;
    mainColFrame.w = (parts.topRight->getPos().x - pos.x) / p_scale;
    mainColFrame.h = (parts.bottomLeft->getPos().y - pos.y) / p_scale;

    mainCollider = new Collider(mainColFrame, this, 2);
}