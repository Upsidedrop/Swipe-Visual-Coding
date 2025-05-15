#include "Loop.hpp"

const int DEFAULT_LOOP_SIZE = 24;

Loop::Loop(Vector2f p_pos, float p_scale, SDL_Texture* p_tex, BlockType p_type, SDL_Rect p_frame, const char* p_text, Vector2f textOffset)
:Block(p_pos, p_tex, p_frame, p_type, p_scale, p_text, textOffset), innerChild(nullptr), bodySize(10) {
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

    body = new Entity(p_pos + Vector2f(0, p_frame.h * p_scale), p_tex, bodyFrame, Vector2f(p_scale, (DEFAULT_LOOP_SIZE - p_frame.h) * p_scale));
    foot = new Entity(p_pos + Vector2f(0, DEFAULT_LOOP_SIZE * p_scale), p_tex, footFrame, Vector2f(p_scale, p_scale));

    float a = (footFrame.x + footFrame.w) * p_scale;
    float b = text.getDimensions().x;

    footMiddle = new Entity(Vector2f(a, DEFAULT_LOOP_SIZE * p_scale) + p_pos, p_tex, footMiddleFrame, Vector2f((b - a + textOffset.x * 2) / footMiddleFrame.w, p_scale));
    footEnd = new Entity(Vector2f((a < b + textOffset.x * 2)? b + textOffset.x * 2: a, DEFAULT_LOOP_SIZE * p_scale) + p_pos, p_tex, footEndFrame, Vector2f(p_scale, p_scale));

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