#pragma once

#include "DividedEntity.hpp"
#include "Collider.hpp"

class Gap;
class TextBox;

class HeightChanger{
    DividedEntity& parts;
    int baseHeight;
    HeightChanger* parent;
    int minHeight;
    std::vector<std::pair<TextBox*, Gap*>>& parameters;
    Collider*& col;
    float& textOffsetY;

    std::vector<int> GetArgumentHeights();

    public:
    std::vector<std::pair<Vector2f, Vector2f>>* parameterOffsets;
    void UpdateHeight();
        HeightChanger(DividedEntity& p_parts, int p_baseHeight, HeightChanger* p_parent, int p_minHeight, std::vector<std::pair<TextBox*, Gap*>>& p_parameters, Collider*& p_col, float& p_textOffsetY)
    :parts(p_parts), baseHeight(p_baseHeight), parent(p_parent), minHeight(p_minHeight), parameters(p_parameters), col(p_col), textOffsetY(p_textOffsetY), parameterOffsets(nullptr){};
};