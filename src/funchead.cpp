#include "FuncHead.hpp"

FuncHead::FuncHead(Vector2f p_pos, float p_scale, SDL_Texture* p_tex, BlockType p_type , SDL_Rect p_frame, std::string p_name, Vector2f p_textOffset, std::vector<const char*> p_parameters)
:Block(p_pos, p_tex, p_frame, p_type, p_scale, p_name.c_str(), p_textOffset, p_parameters){    
    parts.limits.y = 17;

    SDL_FRect bottomColRect;
    bottomColRect = bottomCollider->GetFrame();
    bottomColRect.y += 3;
    bottomCollider -> SetFrame(bottomColRect);

    functions[p_name] = this;

    SDL_Rect centerSize;
    centerSize.x = 27;
    centerSize.y = 4;
    centerSize.w = 25;
    centerSize.h = 11;

    BlockResize::InitBlockScale(
        centerSize, parts, p_scale, text, p_textOffset, parameters, p_pos, parameterOffsets, p_tex, p_parameters, heightChanger, this, true
    );
    for(auto pair : parameters){
        pair.first -> getVisual() -> SetLayer(layer + 1);
        pair.second -> SetLayer(layer + 1);
    }

    mainCollider = parts.GenerateGrabbableCollider(this);

    if (parameters.size() != 0)
    {
        heightChanger.UpdateHeight();
    }
}
void FuncHead::setPos(Vector2f p_pos){
    pos = p_pos;
    //currentFrame > -2 < is to account for dip at bottom of block and top of other block
    if(child != nullptr)
    {
        SDL_Rect foo = parts.bottomLeft->getCurrentFrame();
        child-> setPos(p_pos + Vector2f(0, (foo.y + foo.h - 2) * scale.y));
    }
    text.getVisual() -> setPos(p_pos + textOffset); 
    
    parts.top -> setPos(Vector2f(p_pos.x + currentFrame.w * scale.x, p_pos.y));
    parts.topRight -> setPos(Vector2f(p_pos.x + currentFrame.w * scale.x + parts.top -> getCurrentFrame().w * parts.top->getScale().x, p_pos.y));
    
    Vector2f topMargin(0, parts.left->getCurrentFrame().y * scale.y);

    parts.left -> setPos(p_pos + topMargin);
    parts.center -> setPos(parts.top -> getPos() + topMargin);
    parts.right -> setPos(parts.topRight -> getPos() + topMargin);

    topMargin.y = parts.bottomLeft->getCurrentFrame().y * scale.y;

    parts.bottomLeft -> setPos(p_pos + topMargin);
    parts.bottom -> setPos(parts.top -> getPos() + topMargin);
    parts.bottomRight -> setPos(parts.topRight -> getPos() + topMargin);
    
    MoveParameters(p_pos);
}