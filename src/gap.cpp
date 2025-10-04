#include "Gap.hpp"
#include "Utils.hpp"
#include "Block.hpp"

constexpr int HALF_GAP = 12;

Gap::Gap(Vector2f p_pos, HeightChanger& p_heightChanger, void* p_identity, bool p_isBlock, Vector2f p_scale, int p_layer)
:Entity(p_pos, gapTexture, utils::InitRect(0,0,10,7), p_scale, p_layer), attached(nullptr), heightChanger(p_heightChanger), identity(p_identity), isBlock(p_isBlock){
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
    p_attached -> SetLayer(layer + 1);
    p_attached -> SetParent(this);
    
    UpdateSize();
}
void Gap::Detach(){
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
    layers.find(layer) -> second.erase(this);

    layer = p_layer;

    auto it = layers.find(layer);
    if(it == layers.end()){
        layers.insert(std::make_pair(layer, std::unordered_set<Entity*>()));
        it = layers.find(layer); 
    }
    layers.find(layer) -> second.insert(this);

    if(attached != nullptr){
        attached -> SetLayer(p_layer + 1);
    }
}
void Gap::UpdateSize(){
    heightChanger.UpdateHeight();
    if(isBlock){
        ((Block*)(identity)) -> UpdateSize();
    }
    else{
        ((Variable*)(identity)) -> UpdateSize();
    }
}
