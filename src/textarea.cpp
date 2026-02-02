#include "TextArea.hpp"
#include "Utils.hpp"

TextArea::TextArea(Vector2f p_pos, SDL_Texture* p_tex, Vector2f p_textOffset, float p_scale, int p_layer)
:Variable(p_pos, p_tex, " ", p_textOffset, p_scale, p_layer)
{
    auto frame = text.getFrame();
    textCol = new Collider(utils::RectToFrect(frame), this, Collider::TEXT_AREA);
}
void TextArea::setText(const char* p_text){
    text.setText(p_text);
    auto frame = text.getFrame();
    textCol -> SetFrame(utils::RectToFrect(frame));
    UpdateSize();
}
std::string TextArea::getText(){
    return text.getText();
}
bool TextArea::hasText(){
    return true;
}
