#include "Variable.hpp"

Variable::Variable(){
    SDL_Rect bodyFrame;
    bodyFrame.x = 0;
    bodyFrame.y = 0;
    bodyFrame.w = 10;
    bodyFrame.h = 7;
    visual = new Entity(Vector2f(200,300), varTexture, bodyFrame, Vector2f(4,4));
}
Variable::~Variable(){
    delete visual;
}