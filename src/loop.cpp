#include "Loop.hpp"

Loop::Loop(Vector2f p_pos, Vector2f p_scale, SDL_Texture* p_tex, std::map<int, std::unordered_set<Entity*>>* p_layers)
:pos(p_pos), scale(p_scale){
    SDL_Rect headFrame;
    headFrame.x = 0;
    headFrame.y = 0;
    headFrame.w = 63;
    headFrame.h = 12;
    SDL_Rect bodyFrame;
    bodyFrame.x = 0;
    bodyFrame.y = 11;
    bodyFrame.w = 5;
    bodyFrame.h = 1;
    SDL_Rect footFrame;
    footFrame.x = 0;
    footFrame.y = 12;
    footFrame.w = 63;
    footFrame.h = 6;
    head = new Entity(p_pos, p_tex, p_layers, headFrame, p_scale);
    body = new Entity(p_pos + Vector2f(0, 12), p_tex, p_layers, bodyFrame, Vector2f(p_scale.x, 8));
    foot = new Entity(p_pos + Vector2f(0, 20), p_tex, p_layers, footFrame, p_scale);
}
Loop::~Loop(){
    delete head;
    delete body;
    delete foot;
}