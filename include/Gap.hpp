#pragma once

#include "Entity.hpp"
#include "Math.hpp"
#include "Variable.hpp"

class Block;

extern SDL_Texture* gapTexture;

class Gap : public Entity{
    public:
    Gap(Vector2f p_pos, Block* p_parent, Vector2f p_scale = Vector2f(4,4), int p_layer = 0);
    ~Gap();
    float GetSize();
    void SetAttached(Variable* p_attached);
    void setPos(Vector2f p_pos) override {
        pos = p_pos;
        if(attached != nullptr){
            attached -> setPos(p_pos);
        }
    }
    void SetLayer(int p_layer) override{
        layers.find(layer) -> second.erase(this);

        layer = p_layer;

        auto it = layers.find(layer);
        if(it == layers.end()){
            layers.insert(std::make_pair(layer, std::unordered_set<Entity*>()));
            it = layers.find(layer); 
        }
        layers.find(layer) -> second.insert(this);

        if(attached != nullptr){
            attached -> SetLayer(p_layer + 1);
        }
    }
    void Detach();
    private:
    Variable* attached;
    Collider* col;
    Block* parent;
};