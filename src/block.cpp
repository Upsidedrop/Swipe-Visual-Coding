#include "Block.hpp"

LinkedList<Block> Block::blocks;

Block::Block(Vector2f p_pos, SDL_Texture *p_tex, SDL_Rect p_frame, BlockType p_type, float p_scale, const char *p_text, Vector2f p_textOffset, std::vector<const char*> p_parameters)
    : Entity(p_pos, p_tex, p_frame, Vector2f(p_scale, p_scale)), topCollider(nullptr), child(nullptr), parent(nullptr), type(p_type), text(p_text, p_pos + p_textOffset, 0.6), textOffset(p_textOffset), heightChanger(parts, 7, nullptr, 14), parts(Vector2f(65, 14))
{
    std::cout << "Block init" << "\n";
    std::cout << p_type << "\n";
    if (p_type != BlockType::DEFAULTHEAD)
    {
        SDL_FRect topColFrame;
        topColFrame.x = 0;
        topColFrame.y = 0;
        topColFrame.w = 32;
        topColFrame.h = 0;

        topCollider = new Collider(topColFrame, this, 0);
    }

    SDL_FRect bottomColFrame;
    bottomColFrame.x = 0;
    bottomColFrame.y = 12;
    bottomColFrame.w = 32;
    bottomColFrame.h = 8;

    bottomCollider = new Collider(bottomColFrame, this, 1);

    if (p_type != BlockType::DEFAULTHEAD)
    {
        blocks.Add(this);

        SDL_Rect centerSize;
        centerSize.x = 14;
        centerSize.y = 4;
        centerSize.w = 48;
        centerSize.h = 6;
        
        if(p_type == BlockType::DEFAULTLOOP){
            centerSize.x = 20;
            centerSize.w = 42;
        }

        BlockResize::InitBlockScale(
            centerSize, parts, p_scale, text, p_textOffset, parameters, p_pos, parameterOffsets, p_tex, p_parameters, heightChanger
        );

        SDL_FRect mainColFrame;
        mainColFrame.x = 0;
        mainColFrame.y = 0;
        mainColFrame.w = (parts.topRight->getPos().x - pos.x) / p_scale;
        mainColFrame.h = (parts.bottomLeft->getPos().y - pos.y) / p_scale;

        mainCollider = new Collider(mainColFrame, this, 2);


        for(auto pair : parameters){
            pair.first -> getVisual() -> SetLayer(layer + 1);

            pair.second -> SetLayer(layer + 1);
        }
    }
}
Block::~Block()
{
    delete mainCollider;
    delete topCollider;
    delete bottomCollider;
}
float Block::GetBottom()
{
    return parts.bottom->getPos().y + (parts.bottom->getCurrentFrame().h - 1) * scale.y;
}
void Block::ToggleIsContained(bool p_contained)
{
    contained = p_contained;
    if (child != nullptr)
    {
        child->ToggleIsContained(p_contained);
    }
}
void Block::setChild(Block *p_child)
{
    child = p_child;
    child->ToggleIsContained(contained);
    if (contained)
    {
        Block *loopIt = this;
        while (loopIt->getParent()->getChild() == loopIt)
        {
            loopIt = loopIt->getParent();
            if (loopIt == nullptr)
            {
                std::cout << "something wicked this way comes" << "\n";
            }
        }
        Block *childIt = this;
        while (childIt->getChild() != nullptr)
        {
            std::cout << childIt->getChild() << "\n";
            childIt = childIt->getChild();
        }
        loopIt->getParent()->setBodySize((childIt->GetBottom() - loopIt->getParent()->getPos().y) / scale.y - (/*total head height*/ (parts.bottom->getPos().y - pos.y) / scale.y + parts.bottom->getCurrentFrame().h));
    }
}
void Block::RemoveChild()
{
    if (contained)
    {
        Block *it = this;
        while (it->getParent()->getChild() == it)
        {
            it = it->getParent();
            if (it == nullptr)
            {
                std::cout << "something wicked this way comes" << "\n";
            }
        }
        it->getParent()->setBodySize((GetBottom() - it->getParent()->getPos().y) / scale.y - currentFrame.h);

        child->ToggleIsContained(false);
    }
    child = nullptr;
}