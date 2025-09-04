#pragma once

#include <SDL2/SDL_image.h>

#include "Collider.hpp"
#include "TextBox.hpp"
#include "DividedEntity.hpp"
#include "HeightChanger.hpp"

class Gap;

class Variable : public Entity{
    public:
    Variable(Vector2f p_pos, SDL_Texture* p_tex, const char *p_text, Vector2f p_textOffset, float p_scale = 4, int p_layer = 0, std::vector<const char*> p_parameters = {});
    ~Variable();
    Collider* GetCollider();
    void SetParent(Gap* p_parent);
    Gap* GetParent();
    void setPos(Vector2f p_pos) override{
        pos = p_pos;

        float a = (currentFrame.x + currentFrame.w) * scale.x;
        float b = text.getDimensions().x + currentFrame.w * scale.x;

        parts.top -> setPos(Vector2f(a + p_pos.x, p_pos.y));
        parts.topRight -> setPos(Vector2f(((a < b) ? b : a) + p_pos.x, p_pos.y));

        text.getVisual() -> setPos(Vector2f(p_pos.x + currentFrame.w * scale.x, pos.y));
    }
    void SetLayer(int p_layer) override{
        parts.top -> SetLayer(p_layer);
        parts.topRight -> SetLayer(p_layer);

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
    Vector2f textOffset;
    TextBox text;
    std::vector<std::pair<TextBox*, Gap*>> parameters;
    std::vector<std::pair<Vector2f, Vector2f>> parameterOffsets;
    HeightChanger heightChanger;
    DividedEntity parts;
};