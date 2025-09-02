#pragma once

#include <vector>

#include "TextBox.hpp"
#include "Gap.hpp"
#include "DividedEntity.hpp"
#include "HeightChanger.hpp"

class Block;

namespace BlockResize{
    void InitBlockScale( 
                        SDL_Rect& p_centerFrame, DividedEntity& p_parts, float p_scale, 
                        TextBox& p_text, Vector2f& p_textOffset, std::vector<std::pair<TextBox*, Gap*>>& p_outParameters, 
                        Vector2f& p_pos, std::vector<std::pair<Vector2f, Vector2f>>& p_parameterOffsets, SDL_Texture* p_tex,
                        std::vector<const char*> p_inParameters, HeightChanger& p_heightChanger);
    void UpdateBlockScale(
        SDL_Rect& p_currentFrame, TextBox& p_text, Vector2f& p_scale,
        Vector2f& p_textOffset, std::vector<std::pair<TextBox*, Gap*>>& p_parameters,
        std::vector<std::pair<Vector2f, Vector2f>>& p_parameterOffsets,
        Vector2f& p_pos, DividedEntity& p_parts
    );
}