#include <vector>

#include "Collider.hpp"

Collider* Collider::CheckForCollisions(std::vector<int> masks){
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
            return other;
        }
    }
    return nullptr;
}