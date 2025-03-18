#include "Block.hpp"

Block::Block(Vector2f p_pos, SDL_Texture* p_tex, map<int, unordered_set<Entity*>>* p_layers, vector<vector<Collider*>>* colliderFlags, SDL_Rect p_frame, Vector2f p_scale)
:Entity(p_pos, p_tex, p_layers, p_frame, p_scale), child(nullptr), parent(nullptr)
{
    SDL_FRect mainColFrame;
    mainColFrame.x = 0;
    mainColFrame.y = 0;
    mainColFrame.w = currentFrame.w;
    mainColFrame.h = currentFrame.h;

    mainCollider = new Collider(mainColFrame, this, colliderFlags, 2);

    SDL_FRect topColFrame;
    topColFrame.x = 0;
    topColFrame.y = -3;
    topColFrame.w = 32;
    topColFrame.h = 8;

    topCollider = new Collider(topColFrame, this, colliderFlags, 0);

    SDL_FRect bottomColFrame;
    bottomColFrame.x = 0;
    bottomColFrame.y = 11;
    bottomColFrame.w = 32;
    bottomColFrame.h = 8;
    
    bottomCollider = new Collider(bottomColFrame, this, colliderFlags, 1);
}
Block::~Block(){
    delete mainCollider;
    delete topCollider;
    delete bottomCollider;
}