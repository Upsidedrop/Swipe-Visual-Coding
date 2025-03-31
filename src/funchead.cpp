#include "FuncHead.hpp"

FuncHead::FuncHead(Vector2f p_pos, Vector2f p_scale, SDL_Texture* p_tex, std::map<int, std::unordered_set<Entity*>>* p_layers, vector<vector<Collider*>>* colliderFlags, BlockType p_type , SDL_Rect p_frame)
:Block(p_pos, p_tex, p_layers, colliderFlags, p_frame, p_type, p_scale)
{
    delete topCollider;
    topCollider = nullptr;
    
    SDL_FRect bottomColRect;
    bottomColRect = bottomCollider->GetFrame();
    bottomColRect.y += 2;
    bottomCollider -> SetFrame(bottomColRect);     
}
