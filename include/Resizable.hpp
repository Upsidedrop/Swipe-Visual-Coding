#pragma once

#include <vector>

#include "TextBox.hpp"
#include "Gap.hpp"

class Block;

namespace BlockResize{
    void InitBlockScale(SDL_Rect& p_frame, SDL_Rect& p_topFrame, SDL_Rect& p_topRightFrame, SDL_Rect& p_leftFrame, 
                        SDL_Rect& p_centerFrame, SDL_Rect& p_rightFrame, SDL_Rect& p_bottomLeftFrame,
                        SDL_Rect& p_bottomFrame, SDL_Rect& p_bottomRightFrame, Entity*& p_left, 
                        Entity*& p_center, Entity*& p_right, Entity*& p_bottomLeft, Entity*& p_bottom, 
                        Entity*& p_bottomRight, float p_scale, TextBox& p_text, Vector2f& p_textOffset,
                        std::vector<std::pair<TextBox*, Gap*>>& p_outParameters, Vector2f& p_pos,
                        std::vector<std::pair<Vector2f, Vector2f>>& p_parameterOffsets, SDL_Texture* p_tex,
                        std::vector<const char*> p_inParameters, Block* p_identity, Entity*& p_top, Entity*& p_topRight);
    void UpdateBlockScale(
        SDL_Rect& p_currentFrame, TextBox& p_text, Vector2f& p_scale,
        Vector2f& p_textOffset, std::vector<std::pair<TextBox*, Gap*>>& p_parameters,
        std::vector<std::pair<Vector2f, Vector2f>>& p_parameterOffsets,
        Vector2f& p_pos, Entity* p_middle, Entity* p_end, Entity* p_center,
        Entity* p_right, Entity* p_bottom, Entity* p_bottomRight
    );
}