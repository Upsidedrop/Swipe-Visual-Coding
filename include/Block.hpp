#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <vector>

#include "Math.hpp"
#include "Collider.hpp"
#include "Entity.hpp"
#include "LinkedList.hpp"
#include "TextBox.hpp"

using std::map;
using std::unordered_set;
using std::vector;

enum BlockType{
    DEFAULT = 1,
    DEFAULTLOOP = 2,
    DEFAULTHEAD = 3
};

class Block : public Entity{
    public:
    Block(Vector2f p_pos, SDL_Texture* p_tex, SDL_Rect p_frame, BlockType p_type, float p_scale = 1, const char* p_text = "Hello World!", Vector2f textOffset = Vector2f(10, 5));
    Collider& getBottomCollider(){
        return *bottomCollider;
    }
    virtual Collider* getTopCollider(){
        return topCollider;
    }
    Block* getChild(){
        return child;
    }
    void ToggleIsContained(bool p_contained);
    virtual float GetBottom();
    void setChild(Block* p_child);
    virtual void setBodySize(float p_size){
        std::cout << "ERROR: DEFAULT BLOCKS DON'T HAVE BODY" << "\n";
    }
    virtual void setChild(Block* p_child, Collider* p_col){
        std::cout << "ERROR: DEFAULT BLOCKS ONLY HAVE ONE COLLIDER" << "\n";
    }
    virtual void RemoveChild(Block* p_child){
        std::cout << "ERROR: DEFAULT BLOCKS ONLY HAVE ONE CHILD" << "\n";
    }
    void RemoveChild();
    Block* getParent(){
        return parent;
    }
    BlockType GetType(){
        return type;
    }

    void setParent(Block* p_parent){
        parent = p_parent;
    }
    void setPos(Vector2f p_pos) override
    {
        pos = p_pos;
        if(child != nullptr)
        {
            child-> setPos(p_pos + Vector2f(0, 12 * scale.y));
        }
        
        middle -> setPos(Vector2f(p_pos.x + 13 * scale.x, p_pos.y));
        end -> setPos(Vector2f(p_pos.x + 13 * scale.x + text.getDimensions().x, p_pos.y));

        text.getVisual() -> setPos(p_pos + Vector2f(10, 5));
    }
    void SetLayer(int p_layer) override{
        if(child != nullptr){
            child -> SetLayer(p_layer);
        }
        text.getVisual() -> SetLayer(p_layer + 1);
        middle ->SetLayer(p_layer);
        end -> SetLayer(p_layer);
        layers.find(layer) -> second.erase(this);

        layer = p_layer;
    
        auto it = layers.find(layer);
        if(it == layers.end()){
            layers.insert(std::make_pair(layer, std::unordered_set<Entity*>()));
            it = layers.find(layer); 
        }
        layers.find(layer) -> second.insert(this);
    }
    virtual ~Block();
    protected:
    static LinkedList<Block> blocks;
    Collider* bottomCollider;
    Collider* topCollider;
    Collider* mainCollider;
    Block* child;
    Block* parent;
    BlockType type;
    bool contained = false;
    TextBox text;
    Entity* middle;
    Entity* end;
};