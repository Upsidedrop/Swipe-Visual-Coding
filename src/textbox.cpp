#include "TextBox.hpp"

TextBox::TextBox(const char* p_text, Vector2f p_pos, SDL_Color p_color){
    std::cout << comic;
    surface = TTF_RenderText_Solid(comic, p_text, p_color);
    std::cout << SDL_GetError();
    tex = window.loadSurface(surface);
    SDL_Rect frame;
    frame.x = 0;
    frame.y = 0;
    SDL_QueryTexture(tex, NULL, NULL, &frame.w, &frame.h);
    visual = new Entity(p_pos, tex, frame);
}
TextBox::~TextBox(){
    SDL_DestroyTexture(tex);
    SDL_FreeSurface(surface);
    delete visual;
}