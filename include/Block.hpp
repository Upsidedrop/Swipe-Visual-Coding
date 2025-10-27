#pragma once

#include <SDL.h>
#include <SDL_image.h>
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
    float GetHeadHeight();
    void setParent(Block* p_parent){
        parent = p_parent;
    }
    
    virtual void UpdateCollider();
    void setPos(Vector2f p_pos) override;
    void SetLayer(int p_layer) override;
    virtual void UpdateSize();
    virtual ~Block();
    protected:
    void MoveParameters(Vector2f p_pos);
    void LayerParameters(int p_layer);
    static LinkedList<Block> blocks;
    Collider* bottomCollider;
    Collider* topCollider;
    Collider* mainCollider;
    Block* child;
    Block* parent;
    BlockType type;
    bool contained = false;
    TextBox text;
    Vector2f textOffset;
    std::vector<std::pair<TextBox*, Gap*>> parameters;
    std::vector<std::pair<Vector2f, Vector2f>> parameterOffsets;
    HeightChanger heightChanger;
    DividedEntity parts;
};
