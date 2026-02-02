#include "TextBox.hpp"

TextBox::TextBox(const char* p_text, Vector2f p_pos, float p_scale, int p_layer, SDL_Color p_color)
:scale(p_scale), color(p_color), text(p_text)
{
    updateTextures();
    visual = new Entity(p_pos, tex, getFrame(), Vector2f(scale, scale), p_layer);
}
void TextBox::setText(const char* p_text){
    switch(strlen(p_text)){
        case 0:
            setRawText(" ");
            break;
        case 2:
            if(p_text[0] == ' '){
                std::cout << p_text[1] + "" << "\n";
                setRawText(&p_text[1]);
                break;
            }
        default:
            setRawText(p_text);
            break;
    }
}
void TextBox::setRawText(const char* p_text){
    text = p_text;
    deleteTextures();
    updateTextures();
    visual -> setTex(tex);
    visual -> setFrame(getFrame());
}
void TextBox::updateTextures(){
    surface = TTF_RenderText_Solid(comic, text.c_str(), color);
    tex = window.loadSurface(surface);
}
void TextBox::deleteTextures(){
    SDL_DestroyTexture(tex);
    SDL_FreeSurface(surface);
}
std::string TextBox::getText(){
    return text;
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