#include "Gap.hpp"
#include "Utils.hpp"
#include "Block.hpp"

constexpr int HALF_GAP = 12;

Gap::Gap(Vector2f p_pos, HeightChanger& p_heightChanger, void* p_identity, bool p_isBlock, Vector2f p_scale, int p_layer)
:Entity(p_pos, gapTexture, utils::InitRect(0,0,10,7), p_scale, p_layer), attached(nullptr), heightChanger(p_heightChanger), identity(p_identity), isBlock(p_isBlock){
    col = new Collider(utils::RectToFrect(currentFrame), this, Collider::GAP);
}
Gap::~Gap(){
    delete col;
}
float Gap::GetSize(){
    return attached == nullptr? 10 : attached -> GetSize();    
}
void Gap::SetAttached(Variable* p_attached){
    if(attached != nullptr){
        Detach();
    }
    attached = p_attached;
    p_attached -> SetLayer(layer);
    p_attached -> SetParent(this);
    
    UpdateSize();
}
void Gap::Detach(){
    attached -> parent = nullptr;
    attached = nullptr;
    
    UpdateSize();
}
float Gap::GetHeight(){
    return (attached != nullptr)? attached -> GetHeight() : 28;
}
void Gap::setPos(Vector2f p_pos){
    pos = p_pos;
    if(attached != nullptr){
        attached -> setPos(Vector2f(pos.x, -(int)(attached -> GetParts().GetFullRect().h / 2) * scale.y + HALF_GAP + pos.y));
    }
}
void Gap::SetLayer(int p_layer){
    SetSelfLayer(p_layer);
    if(attached != nullptr){
        attached -> SetLayer(p_layer);
    }
}
void Gap::UpdateSize(){
    heightChanger.UpdateHeight();
    if(isBlock){
        ((Block*)(identity)) -> UpdateSize();
        ((Block*)(identity)) -> UpdateCollider();
    }
    else{
        ((Variable*)(identity)) -> UpdateSize();
    }
}
Variable* Gap::getAttached(){
    return attached;
}
