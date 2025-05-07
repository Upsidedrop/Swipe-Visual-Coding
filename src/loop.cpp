#include "Loop.hpp"

Loop::Loop(Vector2f p_pos, float p_scale, SDL_Texture* p_tex, BlockType p_type, SDL_Rect p_frame)
:Block(p_pos, p_tex, p_frame, p_type, p_scale), innerChild(nullptr), bodySize(10) {
    SDL_Rect bodyFrame;
    bodyFrame.x = 0;
    bodyFrame.y = 12;
    bodyFrame.w = 7;
    bodyFrame.h = 1;

    SDL_Rect footFrame;
    footFrame.x = 0;
    footFrame.y = 14;
    footFrame.w = 65;
    footFrame.h = 8;

    body = new Entity(p_pos + Vector2f(0, 12 * p_scale), p_tex, bodyFrame, Vector2f(p_scale, 10 * p_scale));
    foot = new Entity(p_pos + Vector2f(0, 22 * p_scale), p_tex, footFrame, Vector2f(p_scale, p_scale));

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
}