#include "Block.hpp"

Block::Block(Vector2f p_pos, SDL_Texture* p_tex, map<int, unordered_set<Entity*>>* p_layers, vector<vector<Collider*>>* colliderFlags, Vector2f p_scale, uint p_w, uint p_h)
:Entity(p_pos, p_tex, p_layers, p_scale, p_w, p_h), child(nullptr), parent(nullptr)
{
    SDL_FRect mainColFrame;
    mainColFrame.x = 0;
    mainColFrame.y = 0;
    mainColFrame.w = p_w;
    mainColFrame.h = p_h;

    mainCollider = Collider(mainColFrame, this, colliderFlags);
    
    (colliderFlags -> data() + 2) -> push_back(&mainCollider);

    SDL_FRect topColFrame;
    topColFrame.x = 0;
    topColFrame.y = -12;
    topColFrame.w = 128;
    topColFrame.h = 32;

    topCollider = Collider(topColFrame, this, colliderFlags);

    colliderFlags -> data() -> push_back(&topCollider);

    SDL_FRect bottomColFrame;
    bottomColFrame.x = 0;
    bottomColFrame.y = 48;
    bottomColFrame.w = 128;
    bottomColFrame.h = 32;
    
    bottomCollider = Collider(bottomColFrame, this, colliderFlags);

    ((colliderFlags -> data()) + 1) -> push_back(&bottomCollider);
}