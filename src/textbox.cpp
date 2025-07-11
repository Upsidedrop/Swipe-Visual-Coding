#include "TextBox.hpp"

TextBox::TextBox(const char* p_text, Vector2f p_pos, float p_scale, int p_layer, SDL_Color p_color)
:scale(p_scale)
{
    surface = TTF_RenderText_Solid(comic, p_text, p_color);
    tex = window.loadSurface(surface);
    SDL_Rect frame;
    frame.x = 0;
    frame.y = 0;
    SDL_QueryTexture(tex, NULL, NULL, &frame.w, &frame.h);
    visual = new Entity(p_pos, tex, frame, Vector2f(scale, scale), p_layer);
}
TextBox::~TextBox(){
    SDL_DestroyTexture(tex);
    SDL_FreeSurface(surface);
    delete visual;
}
float TextBox::getScale(){
    return scale;
}