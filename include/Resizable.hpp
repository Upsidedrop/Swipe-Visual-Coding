#pragma once

#include <vector>

#include "TextBox.hpp"
#include "Gap.hpp"
#include "DividedEntity.hpp"

class Block;

namespace BlockResize{
    void InitBlockScale(SDL_Rect& p_frame, SDL_Rect& p_topFrame, SDL_Rect& p_topRightFrame, SDL_Rect& p_leftFrame, 
                        SDL_Rect& p_centerFrame, SDL_Rect& p_rightFrame, SDL_Rect& p_bottomLeftFrame,
                        SDL_Rect& p_bottomFrame, SDL_Rect& p_bottomRightFrame, DividedEntity& p_parts, float p_scale, 
                        TextBox& p_text, Vector2f& p_textOffset, std::vector<std::pair<TextBox*, Gap*>>& p_outParameters, 
                        Vector2f& p_pos, std::vector<std::pair<Vector2f, Vector2f>>& p_parameterOffsets, SDL_Texture* p_tex,
                        std::vector<const char*> p_inParameters, Block* p_identity);
    void UpdateBlockScale(
        SDL_Rect& p_currentFrame, TextBox& p_text, Vector2f& p_scale,
        Vector2f& p_textOffset, std::vector<std::pair<TextBox*, Gap*>>& p_parameters,
        std::vector<std::pair<Vector2f, Vector2f>>& p_parameterOffsets,
        Vector2f& p_pos, DividedEntity& p_parts
    );
}