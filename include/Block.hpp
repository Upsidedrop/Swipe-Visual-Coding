#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <vector>

#include "Math.hpp"
#include "Collider.hpp"
#include "Entity.hpp"
#include "LinkedList.hpp"
#include "TextBox.hpp"
#include "Gap.hpp"
#include "Resizable.hpp"
#include "DividedEntity.hpp"
#include "HeightChanger.hpp"

using std::map;
using std::unordered_set;
using std::vector;

enum BlockType{
    DEFAULT = 1,
    DEFAULTLOOP = 2,
    DEFAULTHEAD = 3
};

class Block : public Entity{
    const int MIDDLE_TEXTURE_SIZE = 50;
    
    public:
    Block(Vector2f p_pos, SDL_Texture* p_tex, SDL_Rect p_frame, BlockType p_type, float p_scale = 1, const char* p_text = "Hello World!", Vector2f p_textOffset = Vector2f(10, 8), std::vector<const char*> p_parameters = {});
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
    //Often GetBottom() requires "-1" after it. I my brain only has 2 bytes of RAM though so I can't remember why.
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
        
        parts.top -> setPos(Vector2f(p_pos.x + currentFrame.w * scale.x, p_pos.y));
        parts.topRight -> setPos(Vector2f(p_pos.x + currentFrame.w * scale.x + MIDDLE_TEXTURE_SIZE * parts.top->getScale().x, p_pos.y));
        
        Vector2f topMargin(0, 2 * scale.y);

        parts.left -> setPos(p_pos + topMargin);
        parts.center -> setPos(parts.top -> getPos() + topMargin);
        parts.right -> setPos(parts.topRight -> getPos() + topMargin);

        topMargin.y = 12 * scale.y;

        parts.bottomLeft -> setPos(p_pos + topMargin);
        parts.bottom -> setPos(parts.top -> getPos() + topMargin);
        parts.bottomRight -> setPos(parts.topRight -> getPos() + topMargin);

        text.getVisual() -> setPos(p_pos + textOffset);

        for(size_t i = 0; i < parameters.size(); ++i){
            parameters[i].first -> getVisual() -> setPos(parameterOffsets[i].first + p_pos);

            parameters[i].second -> setPos(parameterOffsets[i].second + p_pos);
        }
    }
    void SetLayer(int p_layer) override{
        if(child != nullptr){
            child -> SetLayer(p_layer);
        }
        text.getVisual() -> SetLayer(p_layer + 1);

        for(auto pair : parameters){
            pair.first -> getVisual() -> SetLayer(p_layer + 1);

            pair.second -> SetLayer(p_layer + 1);
        }

        parts.top ->SetLayer(p_layer);
        parts.topRight -> SetLayer(p_layer);

        parts.left -> SetLayer(p_layer);
        parts.center -> SetLayer(p_layer);
        parts.right -> SetLayer(p_layer);

        parts.bottomLeft -> SetLayer(p_layer);
        parts.bottom -> SetLayer(p_layer);
        parts.bottomRight ->SetLayer(p_layer);

        layers.find(layer) -> second.erase(this);

        layer = p_layer;
    
        auto it = layers.find(layer);
        if(it == layers.end()){
            layers.insert(std::make_pair(layer, std::unordered_set<Entity*>()));
            it = layers.find(layer); 
        }
        layers.find(layer) -> second.insert(this);
    }
    virtual void UpdateSize(){
        BlockResize::UpdateBlockScale(
            currentFrame, text, scale,
            textOffset, parameters,
            parameterOffsets,
            pos, parts
        );
        
        SDL_FRect mainColFrame;
        mainColFrame.x = 0;
        mainColFrame.y = 0;
        mainColFrame.w = (parts.topRight->getPos().x - pos.x) / scale.x;
        mainColFrame.h = (parts.bottomLeft->getPos().y - pos.y) / scale.y;

        mainCollider -> SetFrame(mainColFrame);
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
    DividedEntity parts;
    Vector2f textOffset;
    std::vector<std::pair<TextBox*, Gap*>> parameters;
    std::vector<std::pair<Vector2f, Vector2f>> parameterOffsets;
    HeightChanger heightChanger;
};