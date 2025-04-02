#pragma once

#include <functional>

#include "Entity.hpp"
#include "Collider.hpp"

class Button : Entity{
    Button(Vector2f p_pos, SDL_Texture* p_tex, std::map<int, std::unordered_set<Entity*>>* p_layers, SDL_Rect p_frame, Vector2f p_scale = Vector2f(1,1), int p_layer = 0, std::function<void()> p_func, SDL_FRect p_colliderRect, std::vector<std::vector<Collider*>>* colliderFlags)
    :Entity(p_pos, p_tex, p_layers, p_frame, p_scale, p_layer), func(p_func)
    {
        collider = new Collider(p_colliderRect, this, colliderFlags, 4);
    }
    void CallFunc(){
        func();
    }
    ~Button(){
        delete collider;
    }
    private:
    std::function<void()> func;
    Collider* collider;
};