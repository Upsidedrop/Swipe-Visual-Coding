#pragma once

#include <SDL2/SDL_image.h>

#include "Collider.hpp"
#include "TextBox.hpp"

class Gap;

class Variable : public Entity{
    public:
    Variable(Vector2f p_pos, SDL_Texture* p_tex, const char *p_text, float p_scale = 4, int p_layer = 0);
    ~Variable();
    Collider* GetCollider();
    void SetParent(Gap* p_parent);
    Gap* GetParent();
    void setPos(Vector2f p_pos) override{
        pos = p_pos;

        float a = (currentFrame.x + currentFrame.w) * scale.x;
        float b = text.getDimensions().x + currentFrame.w * scale.x;

        middle -> setPos(Vector2f(a + p_pos.x, p_pos.y));
        end -> setPos(Vector2f(((a < b) ? b : a) + p_pos.x, p_pos.y));

        text.getVisual() -> setPos(Vector2f(p_pos.x + currentFrame.w * scale.x, pos.y));
    }
    void SetLayer(int p_layer) override{
        middle -> SetLayer(p_layer);
        end -> SetLayer(p_layer);

        text.getVisual() -> SetLayer(p_layer + 1);

        layer = p_layer;
        
        auto it = layers.find(layer);
        if(it == layers.end()){
            layers.insert(std::make_pair(layer, std::unordered_set<Entity*>()));
            it = layers.find(layer); 
        }
        layers.find(layer) -> second.insert(this);
    }
    float GetSize();
    private:
    Collider* collision;
    Gap* parent;
    Entity* middle;
    Entity* end;
    TextBox text;
};