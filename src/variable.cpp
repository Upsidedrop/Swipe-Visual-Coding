#include "Variable.hpp"
#include "Utils.hpp"

Variable::Variable(Vector2f p_pos, SDL_Texture* p_tex, Vector2f p_scale, int p_layer)
:Entity(p_pos, p_tex, utils::InitRect(0,0,3,7), p_scale, p_layer), parent(nullptr){

    SDL_FRect floatBodyFrame;
    floatBodyFrame.x = currentFrame.x;
    floatBodyFrame.y = currentFrame.y;
    floatBodyFrame.w = currentFrame.w;
    floatBodyFrame.h = currentFrame.h;

    collision = new Collider(floatBodyFrame, this, 4);
}
Variable::~Variable(){
    delete collision;
}
Collider* Variable::GetCollider(){
    return collision;
}
void Variable::SetParent(Gap* p_parent){
    parent = p_parent;
}
Gap* Variable::GetParent(){
    return parent;
}