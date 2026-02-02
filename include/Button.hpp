#pragma once

#include <functional>

#include "Entity.hpp"
#include "Collider.hpp"

class Button : public Entity{
    public:
    Button(Vector2f p_pos, SDL_Texture* p_tex, SDL_Rect p_frame, std::function<void()> p_func, SDL_FRect p_colliderRect, Vector2f p_scale = Vector2f(1,1), int p_layer = 0)
    :Entity(p_pos, p_tex, p_frame, p_scale, p_layer), func(p_func)
    {
        std::cout << "initislized Button\n";
        collider = new Collider(p_colliderRect, this, Collider::BUTTON);
        std::cout << "initislized Collider\n";
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
