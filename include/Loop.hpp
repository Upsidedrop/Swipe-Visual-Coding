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
        foot -> setPos(Vector2f(p_pos.x, p_pos.y + scale.y * (bodySize + 12)));

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
        if(innerChild != nullptr){
            innerChild -> SetLayer(p_layer);
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
            Block* childIt;

            if(innerChild != nullptr){
                childIt = p_child;
                while(childIt -> getChild() != nullptr){
                    childIt = childIt -> getChild();
                }
                innerChild -> setParent(childIt);
                childIt -> setChild(innerChild);
                innerChild -> setPos(Vector2f(childIt -> getPos().x, childIt -> GetBottom()));
            }

            innerChild = p_child;
            
            childIt = innerChild;

            while(childIt -> getChild() != nullptr){
                childIt = childIt -> getChild();
            }
            setBodySize((childIt -> GetBottom() - pos.y) / scale.y - currentFrame.h);
            innerChild -> ToggleIsContained(true);
        }
    }
    void setBodySize(float p_size) override{
        bodySize = p_size;
        body -> setScale(Vector2f(scale.x, scale.y * p_size));
        foot -> setPos(Vector2f(pos.x, pos.y + scale.y * (p_size + 12)));

        SDL_FRect bottomColFrame;
        bottomColFrame.x = 0;
        bottomColFrame.y = 16 + p_size;
        bottomColFrame.w = 32;
        bottomColFrame.h = 8;

        bottomCollider -> SetFrame(bottomColFrame);
    }
    void RemoveChild(Block* p_child) override{
        if(p_child == child){
            child = nullptr;
        }
        else{
            innerChild -> ToggleIsContained(false);
            setBodySize(currentFrame.h - 2);
            innerChild = nullptr;
        }
    }
    private:
    Entity* body;
    Entity* foot;
    Collider* innerCollider;
    Block* innerChild;
    uint bodySize;
};