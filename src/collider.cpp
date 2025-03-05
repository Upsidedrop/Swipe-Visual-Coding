#include <vector>

#include "Collider.hpp"
#include "Block.hpp"

using namespace std;

Collider* Collider::CheckForCollisions(vector<int> masks){
    for(int i : masks){
        for(Collider* other : *(flags -> data() + i)){
            if((other -> GetParent() -> getPos().x + other -> GetFrame().w + other -> GetFrame().x) < (parent -> getPos().x) + frame.x){
                continue;
            }
            if((other -> GetParent() -> getPos().y + other -> GetFrame().h + other -> GetFrame().y) < (parent -> getPos().y) + frame.y){
                continue;
            }
            if((parent -> getPos().x + frame.w + frame.x) < (other -> GetParent() -> getPos().x) + other -> GetFrame().x){
                continue;
            }
            if((parent -> getPos().y + frame.h + frame.y) < (other -> GetParent() -> getPos().y) + other -> GetFrame().y){
                continue;
            }
            return other;
        }
    }
    return nullptr;
}