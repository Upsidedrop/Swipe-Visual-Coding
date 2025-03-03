#include "Entity.hpp"

Entity::Entity(Vector2f p_pos, SDL_Texture* p_tex, Vector2f p_scale, uint p_w, uint p_h)
:pos(p_pos), scale(p_scale), tex(p_tex)
{

    currentFrame.x = 0;
    currentFrame.y = 0;
    currentFrame.w = p_w;
    currentFrame.h = p_h;
}
SDL_Texture* Entity::getTex(){
    return tex;
}
SDL_Rect Entity::getCurrentFrame(){
    return currentFrame;
}