#pragma once

#include "Entity.hpp"
#include "Block.hpp"
#include "Math.hpp"

class Loop : Block{
    public:
    Loop(Vector2f p_pos, Vector2f p_scale, SDL_Texture* p_tex, std::map<int, std::unordered_set<Entity*>>* p_layers, vector<vector<Collider*>>* colliderFlags, SDL_Rect p_frame);
    ~Loop();
    Collider* GetInnerCollider(){
        return innerCollider;
    }
    void setPos(Vector2f p_pos) override
    {
        pos = p_pos;

        body -> setPos(p_pos + Vector2f(0, 12 * scale.y));
        foot -> setPos(p_pos + Vector2f(0, 22 * scale.y));
        if(child != nullptr)
        {
            child-> setPos(p_pos + Vector2f(0, 27 * scale.y));
        }
    }
    void SetLayer(int p_layer) override{
        if(child != nullptr){
            child -> SetLayer(p_layer);
        }
        body -> SetLayer(p_layer);
        foot -> SetLayer(p_layer);

        layers -> find(layer) -> second.erase(this);

        layer = p_layer;
    
        auto it = layers -> find(layer);
        if(it == layers -> end()){
            layers -> insert(std::make_pair(layer, std::unordered_set<Entity*>()));
            it = layers -> find(layer); 
        }
        layers -> find(layer) -> second.insert(this);
    }
    private:
    Entity* body;
    Entity* foot;
    Collider* innerCollider;
};