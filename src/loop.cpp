#include "Loop.hpp"

Loop::Loop(Vector2f p_pos, Vector2f p_scale, SDL_Texture* p_tex, std::map<int, std::unordered_set<Entity*>>* p_layers, BlockType p_type, SDL_Rect p_frame)
:Block(p_pos, p_tex, p_layers, p_frame, p_type, p_scale), innerChild(nullptr), bodySize(10) {
    SDL_Rect bodyFrame;
    bodyFrame.x = 0;
    bodyFrame.y = 11;
    bodyFrame.w = 5;
    bodyFrame.h = 1;

    SDL_Rect footFrame;
    footFrame.x = 0;
    footFrame.y = 12;
    footFrame.w = 63;
    footFrame.h = 6;

    body = new Entity(p_pos + Vector2f(0, 12 * p_scale.y), p_tex, p_layers, bodyFrame, Vector2f(p_scale.x, 10 * p_scale.y));
    foot = new Entity(p_pos + Vector2f(0, 22 * p_scale.y), p_tex, p_layers, footFrame, p_scale);

    SDL_FRect bottomColFrame;
    bottomColFrame.x = 0;
    bottomColFrame.y = 27;
    bottomColFrame.w = 32;
    bottomColFrame.h = 8;

    bottomCollider -> SetFrame(bottomColFrame);

    SDL_FRect innerColliderFrame;
    innerColliderFrame.x = 5;
    innerColliderFrame.y = 11;
    innerColliderFrame.w = 32;
    innerColliderFrame.h = 8;

    innerCollider = new Collider(innerColliderFrame, this, 1);
}
Loop::~Loop(){
   delete body;
   delete foot;
   delete innerCollider;
}