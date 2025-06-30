#include "Gap.hpp"
#include "Utils.hpp"

Gap::Gap(Vector2f p_pos, Block* p_parent, Vector2f p_scale, int p_layer)
:Entity(p_pos, gapTexture, utils::InitRect(0,0,10,7), p_scale, p_layer), attached(nullptr), parent(p_parent){
    col = new Collider(utils::RectToFrect(currentFrame), this, 5);
}
Gap::~Gap(){
    delete col;
}
float Gap::GetSize(){
    return attached == nullptr? 10 : attached -> GetSize();    
}
void Gap::SetAttached(Variable* p_attached){
    attached = p_attached;
    p_attached -> setPos(pos);
    p_attached -> SetLayer(layer + 1);
    p_attached -> SetParent(this);
    parent -> UpdateSize();
}
void Gap::Detach(){
    attached = nullptr;
    parent -> UpdateSize();
}