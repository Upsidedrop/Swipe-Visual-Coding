#include "Block.hpp"

Block::Block(Vector2f p_pos, SDL_Texture* p_tex, map<int, unordered_set<Entity*>>* p_layers, vector<vector<Collider*>>* colliderFlags, SDL_Rect p_frame, BlockType p_type , Vector2f p_scale)
:Entity(p_pos, p_tex, p_layers, p_frame, p_scale), child(nullptr), parent(nullptr), type(p_type)
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
float Block::GetBottom(){
    return pos.y + currentFrame.h * scale.y;
}
void Block::ToggleIsContained(bool p_contained){
    contained = p_contained;
    if(child != nullptr){
        child -> ToggleIsContained(p_contained);
    }
}
void Block::setChild(Block* p_child){
    child = p_child;
    child -> ToggleIsContained(contained);
    if(contained){
        Block* loopIt = this;
        while(loopIt -> getParent() -> GetType() < 2 && loopIt -> getParent() -> getChild() == loopIt){
            loopIt = loopIt -> getParent();
            if(loopIt == nullptr){
                std::cout << "something wicked this way comes" << "\n";
            }
        }
        Block* childIt = this;
        while(childIt -> getChild() != nullptr){
            std::cout<< childIt -> getChild() << "\n";
            childIt = childIt -> getChild();
        }
        loopIt -> getParent() -> setBodySize((childIt -> GetBottom() - loopIt -> getParent() -> getPos().y) / scale.y - currentFrame.h - 1);
    }
}
void Block::RemoveChild(){
    if(contained){
        Block* it = this;
        while(it -> getParent() -> GetType() < 2 && it -> getParent() -> getChild() == it){
            it = it -> getParent();
            if(it == nullptr){
                std::cout << "something wicked this way comes" << "\n";
            }
        }
        it -> getParent() -> setBodySize((GetBottom() - it -> getParent() -> getPos().y) / scale.y - currentFrame.h - 1);

        child -> ToggleIsContained(false);
    }
    child = nullptr;
}