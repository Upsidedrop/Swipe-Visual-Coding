#pragma once

#include "Entity.hpp"
#include "Block.hpp"
#include "Math.hpp"

class Loop : public Block{
    const int MIDDLE_TEXTURE_SIZE = 44;
    const int TOTAL_TEXTURE_HEIGHT = 21;

    public:
    Loop(Vector2f p_pos, float p_scale, SDL_Texture* p_tex, BlockType p_type , SDL_Rect p_frame, const char* p_text = "Hello World!", Vector2f p_textOffset = Vector2f(10, 9));
    ~Loop();
    Collider* GetInnerCollider(){
        return innerCollider;
    }
    void setPos(Vector2f p_pos) override
    {
        pos = p_pos;

        text.getVisual() -> setPos(p_pos + textOffset);
        
        body -> setPos(p_pos + Vector2f(0, (currentFrame.h - 1) * scale.y));
        foot -> setPos(Vector2f(p_pos.x, p_pos.y + scale.y * (bodySize + currentFrame.h - 1)));

        middle -> setPos(Vector2f(p_pos.x + currentFrame.w * scale.x, p_pos.y));
        end -> setPos(Vector2f(p_pos.x + currentFrame.w * scale.x + MIDDLE_TEXTURE_SIZE * middle->getScale().x, p_pos.y));

        footMiddle -> setPos(Vector2f(p_pos.x + currentFrame.w * scale.x, foot->getPos().y));
        footEnd -> setPos(Vector2f(p_pos.x + currentFrame.w * scale.x + MIDDLE_TEXTURE_SIZE * middle->getScale().x, foot->getPos().y));

        if(child != nullptr)
        {
            child -> setPos(p_pos + Vector2f(bottomCollider->GetFrame().x * scale.x, bottomCollider->GetFrame().y * scale.y));
        }
        if(innerChild != nullptr){
            innerChild -> setPos(p_pos + Vector2f(innerCollider->GetFrame().x * scale.x, innerCollider->GetFrame().y * scale.y));
        }
    }
    float GetBottom() override{
        return pos.y + scale.y * (bodySize + TOTAL_TEXTURE_HEIGHT - 1);
    }
    void SetLayer(int p_layer) override{
        if(child != nullptr){
            child -> SetLayer(p_layer);
        }
        if(innerChild != nullptr){
            innerChild -> SetLayer(p_layer);
        }
        text.getVisual() -> SetLayer(p_layer + 1);
        body -> SetLayer(p_layer);
        foot -> SetLayer(p_layer);

        layers.find(layer) -> second.erase(this);

        layer = p_layer;
    
        auto it = layers.find(layer);
        if(it == layers.end()){
            layers.insert(std::make_pair(layer, std::unordered_set<Entity*>()));
            it = layers.find(layer); 
        }
        layers.find(layer) -> second.insert(this);
    }
    Block* GetInnerChild(){
        return innerChild;
    }
    void setChild(Block* p_child, Collider* p_col) override{
        if(p_col == bottomCollider){
            child = p_child;
            child -> ToggleIsContained(contained);
            if(contained){
                Block* loopIt = this;
                while(loopIt -> getParent() -> getChild() == loopIt){
                    loopIt = loopIt -> getParent();
                    if(loopIt == nullptr){
                        std::cout << "something wicked this way comes" << "\n";
                    }
                }
                Block* childIt = this;
                while(childIt -> getChild() != nullptr){
                    std::cout<< childIt -> getChild() << "\n";
                    childIt = childIt -> getChild();
                }
                loopIt -> getParent() -> setBodySize((childIt -> GetBottom() - loopIt -> getParent() -> getPos().y) / scale.y - currentFrame.h);
            }
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
                innerChild -> setPos(Vector2f(childIt -> getPos().x, childIt -> GetBottom() - childIt ->getScale().y));
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
        foot -> setPos(Vector2f(pos.x, pos.y + scale.y * (bodySize + currentFrame.h - 1)));

        footMiddle -> setPos(Vector2f(footMiddle -> getPos().x, foot -> getPos().y));
        footEnd -> setPos(Vector2f(footEnd -> getPos().x, foot -> getPos().y));


        if(child != nullptr){
            child -> setPos(Vector2f(pos.x, GetBottom() - child -> getScale().y));
        }
        
        SDL_FRect bottomColFrame;
        bottomColFrame.x = 0;
        bottomColFrame.y = 19 + p_size;
        bottomColFrame.w = 32;
        bottomColFrame.h = 8;

        bottomCollider -> SetFrame(bottomColFrame);

        if(contained){
            Block* it = this;
            while(it -> getParent() -> getChild() == it){
                it = it -> getParent();
                if(it == nullptr){
                    std::cout << "something wicked this way comes" << "\n";
                }
            }
            Block* childIt = this;

            while(childIt -> getChild() != nullptr){
                childIt = childIt -> getChild();
            }

            it -> getParent() -> setBodySize((childIt -> GetBottom() - it -> getParent() -> getPos().y) / scale.y - currentFrame.h);
        }
    }
    void RemoveChild(Block* p_child) override{
        if(p_child == child){
            if(contained){
                Block* it = this;
                while(it -> getParent() -> getChild() == it){
                    it = it -> getParent();
                    if(it == nullptr){
                        std::cout << "something wicked this way comes" << "\n";
                    }
                }
                it -> getParent() -> setBodySize((GetBottom() - it -> getParent() -> getPos().y) / scale.y - currentFrame.h);
            }

            child = nullptr;
        }
        else{
            setBodySize(currentFrame.h - 3);
            innerChild = nullptr;
        }
        p_child -> ToggleIsContained(false);
    }
    private:
    Entity* body;
    Entity* foot;
    Collider* innerCollider;
    Block* innerChild;
    uint bodySize;
    Entity* footMiddle;
    Entity* footEnd;
};