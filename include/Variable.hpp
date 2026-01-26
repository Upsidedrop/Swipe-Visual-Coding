#pragma once

#include <SDL_image.h>
#include <unordered_set>

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
    void setPos(Vector2f p_pos) override;
    void SetLayer(int p_layer) override;
    float GetSize();
    float GetHeight();
    void UpdateSize();
    DividedEntity& GetParts();
    std::vector<std::pair<TextBox*, Gap*>> parameters;
    Gap* parent;
    void trackOwnParameters(std::unordered_set<void*>& p_set);
    protected:
    void MoveParameters(Vector2f p_pos);
    void LayerParameters(int p_layer);
    Collider* collision;
    Vector2f textOffset;
    TextBox text;
    std::vector<std::pair<Vector2f, Vector2f>> parameterOffsets;
    HeightChanger heightChanger;
    DividedEntity parts;
};
