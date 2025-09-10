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

        parts.SetPos(p_pos);

        text.getVisual() -> setPos(p_pos + textOffset);
        MoveParameters(p_pos);
    }
    void SetLayer(int p_layer) override{
        parts.SetLayer(p_layer);

        text.getVisual() -> SetLayer(p_layer + 1);

        LayerParameters(p_layer);

        layer = p_layer;
        
        auto it = layers.find(layer);
        if(it == layers.end()){
            layers.insert(std::make_pair(layer, std::unordered_set<Entity*>()));
            it = layers.find(layer); 
        }
        layers.find(layer) -> second.insert(this);
    }
    float GetSize();

    std::vector<std::pair<TextBox*, Gap*>> parameters;
    private:
    void MoveParameters(Vector2f p_pos);
    void LayerParameters(int p_layer);
    Collider* collision;
    Gap* parent;
    Vector2f textOffset;
    TextBox text;
    std::vector<std::pair<Vector2f, Vector2f>> parameterOffsets;
    HeightChanger heightChanger;
    DividedEntity parts;
};