#include "Loop.hpp"

const int DEFAULT_LOOP_SIZE = 24;

Loop::Loop(Vector2f p_pos, float p_scale, SDL_Texture* p_tex, BlockType p_type, SDL_Rect p_frame, const char* p_text, Vector2f textOffset, std::vector<const char*> p_parameters)
:Block(p_pos, p_tex, p_frame, p_type, p_scale, p_text, textOffset, p_parameters), innerChild(nullptr), bodySize(10) {

    float mainHeight = (parts.bottomLeft->getPos().y - pos.y) / p_scale + parts.bottomLeft -> getCurrentFrame().h;;

    SDL_Rect bodyFrame;
    bodyFrame.x = 0;
    bodyFrame.y = 12;
    bodyFrame.w = 7;
    bodyFrame.h = 1;

    SDL_Rect footFrame;
    footFrame.x = 0;
    footFrame.y = 14;
    footFrame.w = 19;
    footFrame.h = 8;

    SDL_Rect footMiddleFrame;
    footMiddleFrame.x = 19;
    footMiddleFrame.y = 14;
    footMiddleFrame.w = 45;
    footMiddleFrame.h = 8;

    SDL_Rect footEndFrame;
    footEndFrame.x = 64;
    footEndFrame.y = 14;
    footEndFrame.w = 1;
    footEndFrame.h = 8;

    body = new Entity(p_pos + Vector2f(0, mainHeight * p_scale), p_tex, bodyFrame, Vector2f(p_scale, (DEFAULT_LOOP_SIZE - mainHeight) * p_scale));
    foot = new Entity(p_pos + Vector2f(0, DEFAULT_LOOP_SIZE * p_scale), p_tex, footFrame, Vector2f(p_scale, p_scale));

    float a = (footFrame.x + footFrame.w) * p_scale;

    float adjustedMiddleScale = ((currentFrame.w + parts.topRight -> getCurrentFrame().w - footEndFrame.w - footFrame.w) * p_scale + parts.top -> getCurrentFrame().w * parts.top -> getScale().x) / footMiddleFrame.w;

    footMiddle = new Entity(Vector2f(a, DEFAULT_LOOP_SIZE * p_scale) + p_pos, p_tex, footMiddleFrame, Vector2f(adjustedMiddleScale, p_scale));
    footEnd = new Entity(Vector2f(footMiddle -> getScale().x * footMiddleFrame.w + footMiddle -> getPos().x, DEFAULT_LOOP_SIZE * p_scale + p_pos.y), p_tex, footEndFrame, Vector2f(p_scale, p_scale));

    SDL_FRect bottomColFrame;
    bottomColFrame.x = 0;
    bottomColFrame.y = 29;
    bottomColFrame.w = 32;
    bottomColFrame.h = 8;

    bottomCollider -> SetFrame(bottomColFrame);

    SDL_FRect innerColliderFrame;
    innerColliderFrame.x = 6;
    innerColliderFrame.y = 12;
    innerColliderFrame.w = 32;
    innerColliderFrame.h = 8;

    innerCollider = new Collider(innerColliderFrame, this, 1);
}
Loop::~Loop(){
   delete body;
   delete foot;
   delete innerCollider;
   delete footMiddle;
   delete footEnd;
}
void Loop::setPos(Vector2f p_pos){
    float mainHeight = (parts.bottomLeft->getPos().y - pos.y) / scale.y + parts.bottomLeft -> getCurrentFrame().h;
    
    pos = p_pos;

    text.getVisual() -> setPos(p_pos + textOffset);
    
    body -> setPos(p_pos + Vector2f(0, (mainHeight- 1) * scale.y));
    foot -> setPos(Vector2f(p_pos.x, p_pos.y + scale.y * (bodySize + mainHeight - 1)));

    parts.SetPos(p_pos);

    footMiddle -> setPos(Vector2f(p_pos.x + foot -> getCurrentFrame().w * scale.x, foot->getPos().y));
    footEnd -> setPos(Vector2f(footMiddle -> getPos().x + footMiddle -> getCurrentFrame().w * footMiddle -> getScale().x, foot->getPos().y));

    if(child != nullptr)
    {
        child -> setPos(p_pos + Vector2f(bottomCollider->GetFrame().x * scale.x, bottomCollider->GetFrame().y * scale.y));
    }
    if(innerChild != nullptr){
        innerChild -> setPos(p_pos + Vector2f(innerCollider->GetFrame().x * scale.x, innerCollider->GetFrame().y * scale.y));
    }

    MoveParameters(p_pos);
}
void Loop::SetLayer(int p_layer){
    if(child != nullptr){
        child -> SetLayer(p_layer);
    }
    if(innerChild != nullptr){
        innerChild -> SetLayer(p_layer);
    }
    text.getVisual() -> SetLayer(p_layer + 1);

    LayerParameters(p_layer);

    parts.SetLayer(p_layer);

    body -> SetLayer(p_layer);
    foot -> SetLayer(p_layer);

    footMiddle -> SetLayer(p_layer);
    footEnd -> SetLayer(p_layer);

    layers.find(layer) -> second.erase(this);

    layer = p_layer;

    auto it = layers.find(layer);
    if(it == layers.end()){
        layers.insert(std::make_pair(layer, std::unordered_set<Entity*>()));
        it = layers.find(layer); 
    }
    layers.find(layer) -> second.insert(this);
}
void Loop::setChild(Block* p_child, Collider* p_col){
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
            loopIt -> getParent() -> setBodySize((childIt -> GetBottom() - loopIt -> getParent() -> getPos().y) / scale.y - (/*total head height*/ (parts.bottom->getPos().y - pos.y) / scale.y + parts.bottom->getCurrentFrame().h));
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
        setBodySize((childIt -> GetBottom() - pos.y) / scale.y - (/*total head height*/ (parts.bottom->getPos().y - pos.y) / scale.y + parts.bottom->getCurrentFrame().h));
        innerChild -> ToggleIsContained(true);
    }
}
void Loop::setBodySize(float p_size){
    bodySize = p_size;

    body -> setScale(Vector2f(scale.x, scale.y * p_size));
    foot -> setPos(Vector2f(pos.x, pos.y + scale.y * (bodySize + (/*total head height*/ (parts.bottom->getPos().y - pos.y) / scale.y + parts.bottom->getCurrentFrame().h) - 1)));

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

        it -> getParent() -> setBodySize((childIt -> GetBottom() - it -> getParent() -> getPos().y) / scale.y - (/*total head height*/ (parts.bottom->getPos().y - pos.y) / scale.y + parts.bottom->getCurrentFrame().h));
    }
}
void Loop::RemoveChild(Block* p_child){
    if(p_child == child){
        if(contained){
            Block* it = this;
            while(it -> getParent() -> getChild() == it){
                it = it -> getParent();
                if(it == nullptr){
                    std::cout << "something wicked this way comes" << "\n";
                }
            }
            it -> getParent() -> setBodySize((GetBottom() - it -> getParent() -> getPos().y) / scale.y - (/*total head height*/ (parts.bottom->getPos().y - pos.y) / scale.y + parts.bottom->getCurrentFrame().h));
        }

        child = nullptr;
    }
    else{
        setBodySize((/*total head height*/ (parts.bottom->getPos().y - pos.y) / scale.y + parts.bottom->getCurrentFrame().h) - 3);
        innerChild = nullptr;
    }
    p_child -> ToggleIsContained(false);
}
void Loop::UpdateSize(){
    BlockResize::UpdateBlockScale(
        currentFrame, text, scale,
        textOffset, parameters,
        parameterOffsets,
        pos, parts
    );
    
    SDL_FRect mainColFrame;
    mainColFrame.x = 0;
    mainColFrame.y = 0;
    mainColFrame.w = (parts.topRight->getPos().x - pos.x) / scale.x + parts.topRight->getCurrentFrame().w;
    mainColFrame.h = (parts.bottomLeft->getPos().y - pos.y) / scale.y + parts.bottomLeft->getCurrentFrame().h;

    mainCollider -> SetFrame(mainColFrame);

    float adjustedMiddleWidth = ((mainColFrame.w - foot->getCurrentFrame().w - footEnd -> getCurrentFrame().w) * scale.x) / footMiddle -> getCurrentFrame().w;
    footMiddle -> setScale(Vector2f(adjustedMiddleWidth, scale.y));
    footEnd -> setPos(Vector2f(footMiddle -> getPos().x + footMiddle -> getCurrentFrame().w * adjustedMiddleWidth, footMiddle -> getPos().y));
}