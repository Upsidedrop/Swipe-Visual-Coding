#include "Gap.hpp"

Gap::Gap(Vector2f p_pos){
    SDL_Rect bodyFrame;
    bodyFrame.x = 0;
    bodyFrame.y = 0;
    bodyFrame.w = 10;
    bodyFrame.h = 7;
    body = new Entity(p_pos, gapTexture, bodyFrame, Vector2f(4,4),3);
}
Gap::~Gap(){
    delete body;
}
float Gap::GetSize(){
    return 10;    
}