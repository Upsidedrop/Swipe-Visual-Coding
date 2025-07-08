#pragma once

#include <vector>

#include "TextBox.hpp"
#include "Gap.hpp"

class Block;

namespace BlockResize{
    void InitBlockScale(SDL_Rect& p_frame, SDL_Rect& p_middleFrame, SDL_Rect& p_endFrame, float p_scale, 
                        TextBox& p_text, Vector2f& p_textOffset, std::vector<std::pair<TextBox*, Gap*>>& p_outParameters,
                        Vector2f& p_pos, std::vector<std::pair<Vector2f, Vector2f>>& p_parameterOffsets, SDL_Texture* p_tex,
                        std::vector<const char*> p_inParameters, Block* p_identity, Entity*& p_middle, Entity*& p_end);
    void UpdateBlockScale(
        SDL_Rect& p_currentFrame, TextBox& p_text, Vector2f& p_scale,
        Vector2f& p_textOffset, std::vector<std::pair<TextBox*, Gap*>>& p_parameters,
        std::vector<std::pair<Vector2f, Vector2f>>& p_parameterOffsets,
        Vector2f& p_pos, Entity* p_middle, Entity* p_end
    );
}