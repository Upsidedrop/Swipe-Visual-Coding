#include "Variable.hpp"
#include "Utils.hpp"

Variable::Variable(Vector2f p_pos, SDL_Texture* p_tex, const char *p_text, float p_scale, int p_layer)
:Entity(p_pos, p_tex, utils::InitRect(0,0,3,7), Vector2f(p_scale, p_scale), p_layer), parent(nullptr), text(p_text, Vector2f(p_pos.x + currentFrame.w * p_scale, p_pos.y), 0.6){

    SDL_Rect midTexSize = utils::InitRect(3,0,4,7);
    SDL_Rect endTexSize = utils::InitRect(7,0,3,7);

    float a = (currentFrame.x + currentFrame.w) * p_scale;
    float b = text.getDimensions().x + currentFrame.w * p_scale;

    middle = new Entity(Vector2f(a + p_pos.x, p_pos.y), p_tex, midTexSize, Vector2f((b - a) / midTexSize.w, p_scale));
    end = new Entity(Vector2f(((a < b) ? b : a) + p_pos.x, p_pos.y), p_tex, endTexSize, Vector2f(p_scale, p_scale));

    SDL_FRect floatBodyFrame;
    floatBodyFrame.x = currentFrame.x;
    floatBodyFrame.y = currentFrame.y;
    floatBodyFrame.w = currentFrame.w;
    floatBodyFrame.h = currentFrame.h;

    collision = new Collider(floatBodyFrame, this, 4);
}
Variable::~Variable(){
    delete collision;
    delete middle;
    delete end;
}
Collider* Variable::GetCollider(){
    return collision;
}
void Variable::SetParent(Gap* p_parent){
    parent = p_parent;
}
Gap* Variable::GetParent(){
    return parent;
}