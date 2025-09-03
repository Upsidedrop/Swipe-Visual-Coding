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