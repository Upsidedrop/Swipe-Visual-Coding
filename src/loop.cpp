#include "Loop.hpp"

Loop::Loop(Vector2f p_pos, Vector2f p_scale, SDL_Texture* p_tex, std::map<int, std::unordered_set<Entity*>>* p_layers)
:pos(p_pos), scale(p_scale){
    SDL_Rect headFrame;
    headFrame.w = 63;
    headFrame.h = 14;
    head = new Entity(p_pos, p_tex, p_layers, headFrame, p_scale);
    body = new Entity(p_pos, p_tex, p_layers, headFrame, p_scale);
    foot = new Entity(p_pos, p_tex, p_layers, headFrame, p_scale);
}
Loop::~Loop(){
    delete head;
    delete body;
    delete foot;
}