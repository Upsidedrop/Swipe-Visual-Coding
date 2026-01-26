#pragma once

#include "Collider.hpp"
#include "TextBox.hpp"
#include "Variable.hpp"

class TextArea : public Variable{
    public:
    TextArea(Vector2f p_pos, SDL_Texture* p_tex, Vector2f p_textOffset, float p_scale = 4, int p_layer = 0);
    void setText(const char* p_text);
    std::string getText();
    private:
    Collider* textCol;
};