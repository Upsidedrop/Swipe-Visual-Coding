#pragma once

#include "DividedEntity.hpp"

class HeightChanger{
    HeightChanger(DividedEntity& p_parts, int p_baseHeight, HeightChanger& p_parent, int p_minHeight)
    :parts(p_parts), baseHeight(p_baseHeight), parent(p_parent), minHeight(p_minHeight){};

    DividedEntity& parts;
    int baseHeight, minHeight;
    HeightChanger& parent;

    public:
    void UpdateHeight(int height);
};