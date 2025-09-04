#include "Loop.hpp"

const int DEFAULT_LOOP_SIZE = 24;

Loop::Loop(Vector2f p_pos, float p_scale, SDL_Texture* p_tex, BlockType p_type, SDL_Rect p_frame, const char* p_text, Vector2f textOffset, std::vector<const char*> p_parameters)
:Block(p_pos, p_tex, p_frame, p_type, p_scale, p_text, textOffset, p_parameters), innerChild(nullptr), bodySize(10) {

    float mainHeight = (parts.bottomLeft->getPos().y - pos.y) / p_scale + parts.bottomLeft -> getCurrentFrame().h;;

    SDL_Rect bodyFrame;
    bodyFrame.x = 0;
    bodyFrame.y = 12;
    bodyFrame.w = 7;
    bodyFrame.h = 1;

    SDL_Rect footFrame;
    footFrame.x = 0;
    footFrame.y = 14;
    footFrame.w = 19;
    footFrame.h = 8;

    SDL_Rect footMiddleFrame;
    footMiddleFrame.x = 19;
    footMiddleFrame.y = 14;
    footMiddleFrame.w = 45;
    footMiddleFrame.h = 8;

    SDL_Rect footEndFrame;
    footEndFrame.x = 64;
    footEndFrame.y = 14;
    footEndFrame.w = 1;
    footEndFrame.h = 8;

    body = new Entity(p_pos + Vector2f(0, mainHeight * p_scale), p_tex, bodyFrame, Vector2f(p_scale, (DEFAULT_LOOP_SIZE - mainHeight) * p_scale));
    foot = new Entity(p_pos + Vector2f(0, DEFAULT_LOOP_SIZE * p_scale), p_tex, footFrame, Vector2f(p_scale, p_scale));

    float a = (footFrame.x + footFrame.w) * p_scale;

    float adjustedMiddleScale = (currentFrame.w + parts.topRight -> getCurrentFrame().w - footEndFrame.w - footFrame.w) * p_scale + parts.top -> getCurrentFrame().w * parts.top -> getScale().x / (footMiddleFrame.w) * p_scale;

    footMiddle = new Entity(Vector2f(a, DEFAULT_LOOP_SIZE * p_scale) + p_pos, p_tex, footMiddleFrame, Vector2f(adjustedMiddleScale, p_scale));
    footEnd = new Entity(Vector2f(parts.topRight -> getPos().x, DEFAULT_LOOP_SIZE * p_scale + p_pos.y), p_tex, footEndFrame, Vector2f(p_scale, p_scale));

    SDL_FRect bottomColFrame;
    bottomColFrame.x = 0;
    bottomColFrame.y = 29;
    bottomColFrame.w = 32;
    bottomColFrame.h = 8;

    bottomCollider -> SetFrame(bottomColFrame);

    SDL_FRect innerColliderFrame;
    innerColliderFrame.x = 6;
    innerColliderFrame.y = 12;
    innerColliderFrame.w = 32;
    innerColliderFrame.h = 8;

    innerCollider = new Collider(innerColliderFrame, this, 1);
}
Loop::~Loop(){
   delete body;
   delete foot;
   delete innerCollider;
   delete footMiddle;
   delete footEnd;
}