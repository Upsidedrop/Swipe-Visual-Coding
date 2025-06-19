#include "Variable.hpp"

Variable::Variable(Vector2f p_pos, SDL_Texture* p_tex, SDL_Rect p_frame, Vector2f p_scale, int p_layer)
:Entity(p_pos, p_tex, p_frame, p_scale, p_layer){
    SDL_FRect floatBodyFrame;
    floatBodyFrame.x = p_frame.x;
    floatBodyFrame.y = p_frame.y;
    floatBodyFrame.w = p_frame.w;
    floatBodyFrame.h = p_frame.h;

    collision = new Collider(floatBodyFrame, this, 4);
}
Variable::~Variable(){
    delete collision;
}