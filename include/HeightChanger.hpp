#pragma once

#include "DividedEntity.hpp"

class HeightChanger{
    HeightChanger(DividedEntity& p_parts): parts(p_parts){};
    DividedEntity& parts;
    void UpdateHeight(int height){
        height -= parts.top -> getCurrentFrame().h * parts.top -> getScale().y;
        height -= parts.bottom -> getCurrentFrame().h * parts.bottom -> getScale().y;

        parts.left -> setScale(Vector2f(parts.left -> getScale().x, height / parts.left -> getCurrentFrame().h));
        parts.center -> setScale(Vector2f(parts.center -> getScale().x, parts.left -> getScale().y));
        parts.right -> setScale(parts.left -> getScale());

        parts.bottomLeft -> setPos(Vector2f(parts.bottomLeft -> getPos().x, parts.left -> getPos().y + height));
        parts.bottom -> setPos(Vector2f(parts.bottom->getPos().x, parts.bottomLeft -> getPos().y));
        parts.bottomRight -> setPos(Vector2f(parts.bottomRight->getPos().x, parts.bottomLeft -> getPos().y));
    }
};