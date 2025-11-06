#include "Utils.hpp"

Collider* utils::CheckMouseCollisions(Vector2f p_mousePos, vector<int> p_masks){
    for(int i : p_masks){
        for(Collider* other : flags[i]){
            if((other -> GetParent() -> getPos().x + (other -> GetFrame().w + other -> GetFrame().x) * other->GetParent()->getScale().x) < p_mousePos.x){
                continue;
            }
            if((other -> GetParent() -> getPos().y + (other -> GetFrame().h + other -> GetFrame().y) * other->GetParent()->getScale().y) < p_mousePos.y){
                continue;
            }
            if(p_mousePos.x < (other -> GetParent() -> getPos().x) + other -> GetFrame().x){
                continue;
            }
            if(p_mousePos.y < (other -> GetParent() -> getPos().y) + other -> GetFrame().y){
                continue;
            }
            return other;
        }
    }
    return nullptr;
}
void utils::DeconstructFunctionHeads(){
    for(auto functionHeadPair : functions){
        delete functionHeadPair.second;
    }
}
void utils::DeconstructLayers(){
    for(auto layerPair : layers){
        layerPair.second -> FullKill();
    }
}
SDL_FRect utils::RectToFrect(SDL_Rect& p_rect){
    SDL_FRect res;
    res.x = p_rect.x;
    res.y = p_rect.y;
    res.w = p_rect.w;
    res.h = p_rect.h;
    return res;
}
SDL_Rect utils::InitRect(int x, int y, int w, int h){
    SDL_Rect res;
    res.x = x;
    res.y = y;
    res.w = w;
    res.h = h;
    return res;
}
