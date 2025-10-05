#include <vector>
#include <math.h>

#include "Collider.hpp"

constexpr int GAP_ANCHOR_OFFSET = 5;

Collider* Collider::CheckForCollisions(std::vector<int> masks, std::function<bool(Collider*)> p_predicate){
    Collider* closest = nullptr;
    int min = -1;
    Vector2f adjustedPos = parent -> getPos() - Vector2f(GAP_ANCHOR_OFFSET, 0);
    for(int i : masks){
        for(Collider* other : flags[i]){
            if(p_predicate(other)){
                continue;
            }
            if(other == nullptr){
                continue;
            }
            if((other -> GetParent() -> getPos().x + (other -> GetFrame().w + other -> GetFrame().x) * other -> GetParent() -> getScale().x) < (parent -> getPos().x) + frame.x * parent -> getScale().x){
                continue;
            }
            if((other -> GetParent() -> getPos().y + (other -> GetFrame().h + other -> GetFrame().y) * other -> GetParent() -> getScale().y) < (parent -> getPos().y) + frame.y * parent -> getScale().y){
                continue;
            }
            if((parent -> getPos().x + (frame.w + frame.x) * parent -> getScale().x) < (other -> GetParent() -> getPos().x) + other -> GetFrame().x * other -> GetParent() -> getScale().x){
                continue;
            }
            if((parent -> getPos().y + (frame.h + frame.y) * parent -> getScale().y) < (other -> GetParent() -> getPos().y) + other -> GetFrame().y * other -> GetParent() -> getScale().y){
                continue;
            }
            int distance = pow(adjustedPos.x - other -> GetParent() -> getPos().x, 2) + pow(adjustedPos.y - other -> GetParent() -> getPos().y, 2);
            if(distance < min || min == -1){
                closest = other;
                min = distance;
            }
        }
    }
    return closest;
}
Collider* Collider::CheckForCollisionsHeightPriority(std::vector<int> masks){
    //searches for lowest collider, but since the highest point is at y = 0, we search for a collider with the HIGHEST y position
    Collider* lowest = nullptr;
    int max = 0;
    for(int i : masks){
        for(Collider* other : flags[i]){
            if(other == nullptr){
                continue;
            }
            if((other -> GetParent() -> getPos().x + (other -> GetFrame().w + other -> GetFrame().x) * other -> GetParent() -> getScale().x) < (parent -> getPos().x) + frame.x * parent -> getScale().x){
                continue;
            }
            if((other -> GetParent() -> getPos().y + (other -> GetFrame().h + other -> GetFrame().y) * other -> GetParent() -> getScale().y) < (parent -> getPos().y) + frame.y * parent -> getScale().y){
                continue;
            }
            if((parent -> getPos().x + (frame.w + frame.x) * parent -> getScale().x) < (other -> GetParent() -> getPos().x) + other -> GetFrame().x * other -> GetParent() -> getScale().x){
                continue;
            }
            if((parent -> getPos().y + (frame.h + frame.y) * parent -> getScale().y) < (other -> GetParent() -> getPos().y) + other -> GetFrame().y * other -> GetParent() -> getScale().y){
                continue;
            }
            int height = other -> GetParent() -> getPos().y + other -> GetFrame().y * other -> GetParent() -> getScale().y;
            if(height > max){
                max = height;
                lowest = other;
            }
        }
    }
    return lowest;
}
