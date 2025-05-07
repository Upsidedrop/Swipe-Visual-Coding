#include "Block.hpp"

LinkedList<Block> Block::blocks;

Block::Block(Vector2f p_pos, SDL_Texture* p_tex, SDL_Rect p_frame, BlockType p_type, float p_scale, const char* p_text, Vector2f textOffset)
:Entity(p_pos, p_tex, p_frame, Vector2f(p_scale, p_scale)), child(nullptr), parent(nullptr), type(p_type), text(p_text, p_pos + textOffset, 0.8)
{
    SDL_FRect mainColFrame;
    mainColFrame.x = 0;
    mainColFrame.y = 0;
    mainColFrame.w = currentFrame.w;
    mainColFrame.h = currentFrame.h;

    mainCollider = new Collider(mainColFrame, this, 2);

    SDL_FRect topColFrame;
    topColFrame.x = 0;
    topColFrame.y = -3;
    topColFrame.w = 32;
    topColFrame.h = 8;

    topCollider = new Collider(topColFrame, this, 0);

    SDL_FRect bottomColFrame;
    bottomColFrame.x = 0;
    bottomColFrame.y = 11;
    bottomColFrame.w = 32;
    bottomColFrame.h = 8;
    
    bottomCollider = new Collider(bottomColFrame, this, 1);
    if(type != BlockType::DEFAULTHEAD){
        blocks.Add(this);
    }

    SDL_Rect middleSize;
    middleSize.x = 12;
    middleSize.y = 0;
    middleSize.w = 50;
    middleSize.h = 12;

    middle = new Entity(Vector2f(p_pos.x + 12 * p_scale, p_pos.y), p_tex, middleSize, Vector2f((text.getDimensions().x) / middleSize.w, p_scale));

    SDL_Rect endSize;
    endSize.x = 62;
    endSize.y = 0;
    endSize.w = 1;
    endSize.h = 12;

    end = new Entity(Vector2f(p_pos.x + 12 * p_scale + text.getDimensions().x, p_pos.y), p_tex, endSize, Vector2f(p_scale, p_scale), 5);
}
Block::~Block(){
    delete mainCollider;
    delete topCollider;
    delete bottomCollider;
    delete middle;
    delete end;
}
float Block::GetBottom(){
    return pos.y + (currentFrame.h - 1) * scale.y;
}
void Block::ToggleIsContained(bool p_contained){
    contained = p_contained;
    if(child != nullptr){
        child -> ToggleIsContained(p_contained);
    }
}
void Block::setChild(Block* p_child){
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
void Block::RemoveChild(){
    if(contained){
        Block* it = this;
        while(it -> getParent() -> getChild() == it){
            it = it -> getParent();
            if(it == nullptr){
                std::cout << "something wicked this way comes" << "\n";
            }
        }
        it -> getParent() -> setBodySize((GetBottom() - it -> getParent() -> getPos().y) / scale.y - currentFrame.h);

        child -> ToggleIsContained(false);
    }
    child = nullptr;
}