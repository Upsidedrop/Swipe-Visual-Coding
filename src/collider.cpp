#include <vector>

#include "Collider.hpp"
#include "Block.hpp"

using namespace std;

Collider* Collider::CheckForCollisions(vector<int> masks){
    for(int i : masks){
        for(Collider* other : *(flags -> data() + i)){
            if((other -> GetParent() -> getPos().x + other -> GetFrame().w + other -> GetFrame().x) < (parent -> getPos().x) + frame.x){
                cout << 1 << endl;
                continue;
            }
            if((other -> GetParent() -> getPos().y + other -> GetFrame().h + other -> GetFrame().y) < (parent -> getPos().y) + frame.y){
                cout << 2 << endl;
                continue;
            }
            if((parent -> getPos().x + frame.w + frame.x) < (other -> GetParent() -> getPos().x) + other -> GetFrame().x){
                cout << 3 << endl;
                continue;
            }
            if((parent -> getPos().y + frame.h + frame.y) < (other -> GetParent() -> getPos().y) + other -> GetFrame().y){
                cout << 4 << " 1: " << (parent -> getPos().y + frame.h + frame.y) << " 2: " << (other -> GetParent() -> getPos().y) + other -> GetFrame().y << endl;
                //cout << parent << endl;
                continue;
            }
            cout << 5 << endl;
            return other;
        }
    }
    return nullptr;
}