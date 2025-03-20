#pragma once

#include "Entity.hpp"
#include "Block.hpp"
#include "Math.hpp"

class Loop : Block{
    public:
    Loop(Vector2f p_pos, Vector2f p_scale, SDL_Texture* p_tex, std::map<int, std::unordered_set<Entity*>>* p_layers, vector<vector<Collider*>>* colliderFlags, BlockType p_type , SDL_Rect p_frame);
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
            child -> setPos(p_pos + Vector2f(bottomCollider->GetFrame().x * scale.x, bottomCollider->GetFrame().y * scale.y));
        }
        if(innerChild != nullptr){
            innerChild -> setPos(p_pos + Vector2f(innerCollider->GetFrame().x * scale.x, innerCollider->GetFrame().y * scale.y));
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
    Block* GetInnerChild(){
        return innerChild;
    }
    void setChild(Block* p_child, Collider* p_col) override{
        if(p_col == bottomCollider){
            child = p_child;
            child -> ToggleIsContained(contained);
        }
        else
        {
            innerChild = p_child;
            innerChild -> ToggleIsContained(true);
        }
    }
    void setBodySize(float p_size) override{
        body -> setScale(Vector2f(scale.x, scale.y * p_size));
        foot -> setPos(Vector2f(foot -> getPos().x, pos.y + scale.y * (p_size + 12)));
    }
    void RemoveChild(Block* p_child) override{
        if(p_child == child){
            child = nullptr;
        }
        else{
            innerChild = nullptr;
        }
    }
    private:
    Entity* body;
    Entity* foot;
    Collider* innerCollider;
    Block* innerChild;
    float bodySize;
};