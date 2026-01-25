#include "TextBox.hpp"

TextBox::TextBox(const char* p_text, Vector2f p_pos, float p_scale, int p_layer, SDL_Color p_color)
:scale(p_scale)
{
    color = p_color;
    updateTextures(p_text);
    visual = new Entity(p_pos, tex, getFrame(), Vector2f(scale, scale), p_layer);
}
void TextBox::setText(const char* p_text){
    deleteTextures();
    updateTextures(p_text);
    visual -> setTex(tex);
    visual -> setFrame(getFrame());
}
void TextBox::updateTextures(const char* p_text){
    surface = TTF_RenderText_Solid(comic, p_text, color);
    tex = window.loadSurface(surface);
}
void TextBox::deleteTextures(){
    SDL_DestroyTexture(tex);
    SDL_FreeSurface(surface);
}
SDL_Rect TextBox::getFrame(){
    SDL_Rect frame;
    frame.x = 0;
    frame.y = 0;
    SDL_QueryTexture(tex, NULL, NULL, &frame.w, &frame.h);
    return frame;
}
TextBox::~TextBox(){
    deleteTextures();
    delete visual;
}
float TextBox::getScale(){
    return scale;
}