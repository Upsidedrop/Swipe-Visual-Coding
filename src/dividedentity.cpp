#include "DividedEntity.hpp"

void DividedEntity::SetPos(Vector2f& p_pos){
    top->setPos(Vector2f(p_pos.x + top->getCurrentFrame().x * left -> getScale().x, p_pos.y));
    topRight -> setPos(top -> getPos() + Vector2f(top -> getCurrentFrame().w * top -> getScale().x, 0));
    left -> setPos(p_pos + Vector2f(0, left -> getCurrentFrame().y * top -> getScale().y));
    center -> setPos(Vector2f(top -> getPos().x, left -> getPos().y));
    right -> setPos(Vector2f(topRight -> getPos().x, left -> getPos().y));
    bottomLeft -> setPos(left -> getPos() + Vector2f(0, left -> getCurrentFrame().h * left -> getScale().y));
    bottom -> setPos(Vector2f(top -> getPos().x, bottomLeft -> getPos().y));
    bottomRight -> setPos(Vector2f(topRight -> getPos().x, bottomLeft -> getPos().y));
}
Collider* DividedEntity::GenerateGrabbableCollider(Entity* p_identity, int layer){
    
    return new Collider(GetFullRect(), p_identity, layer);
}
void DividedEntity::SetLayer(int p_layer){
    top -> SetLayer(p_layer);
    topRight -> SetLayer(p_layer);
    left -> SetLayer(p_layer);
    center -> SetLayer(p_layer);
    right -> SetLayer(p_layer);
    bottomLeft -> SetLayer(p_layer);
    bottom -> SetLayer(p_layer);
    bottomRight -> SetLayer(p_layer);
}
SDL_FRect DividedEntity::GetFullRect(){
    SDL_FRect hitbox;
    hitbox.x = 0;
    hitbox.y = 0;
    hitbox.w = (topRight->getPos().x - left -> getPos().x) / topRight -> getScale().x + topRight -> getCurrentFrame().w;
    hitbox.h = (bottomLeft->getPos().y - top -> getPos().y) / topRight -> getScale().y + bottomLeft -> getCurrentFrame().h;
    return hitbox;
}