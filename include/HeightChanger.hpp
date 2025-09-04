#pragma once

#include "DividedEntity.hpp"

class HeightChanger{
    DividedEntity& parts;
    int baseHeight;
    HeightChanger* parent;
    int minHeight;

    public:
    void UpdateHeight(int height);
        HeightChanger(DividedEntity& p_parts, int p_baseHeight, HeightChanger* p_parent, int p_minHeight)
    :parts(p_parts), baseHeight(p_baseHeight), parent(p_parent), minHeight(p_minHeight){};
};