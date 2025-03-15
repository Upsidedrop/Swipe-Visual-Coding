#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <vector>

#include "Math.hpp"
#include "Collider.hpp"
#include "Entity.hpp"

using namespace std;

class Block : public Entity{
    public:
    Block(Vector2f p_pos, SDL_Texture* p_tex, map<int, unordered_set<Entity*>>* p_layers, vector<vector<Collider*>>* colliderFlags, SDL_Rect p_frame, Vector2f p_scale = Vector2f(1,1));
    Collider& getBottomCollider(){
        return bottomCollider;
    }
    Collider& getTopCollider(){
        return topCollider;
    }
    Block* getChild(){
        return child;
    }
    void setChild(Block* p_child){
        child = p_child;
    }
    Block* getParent(){
        return parent;
    }

    void setParent(Block* p_parent){
        parent = p_parent;
    }
    void setPos(Vector2f p_pos) override
    {
        pos = p_pos;
        if(child != nullptr)
        {
            child-> setPos(p_pos + Vector2f(0, 11 * scale.y));
        }
    }
    void SetLayer(int p_layer) override{
        if(child != nullptr){
            child -> SetLayer(p_layer);
        }
        layers -> find(layer) -> second.erase(this);

        layer = p_layer;
    
        auto it = layers -> find(layer);
        if(it == layers -> end()){
            layers -> insert(std::make_pair(layer, std::unordered_set<Entity*>()));
            it = layers -> find(layer); 
        }
        layers -> find(layer) -> second.insert(this);
    }
    virtual ~Block() {}
    protected:
    Collider bottomCollider;
    Collider topCollider;
    Collider mainCollider;
    Block* child;
    Block* parent;
};