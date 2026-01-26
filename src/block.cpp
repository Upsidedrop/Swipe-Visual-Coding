#include "Block.hpp"
#include "Utils.hpp"
#include <iostream>

LinkedList<Block> Block::blocks;

Block::Block(Vector2f p_pos, SDL_Texture *p_tex, SDL_Rect p_frame, BlockType p_type, float p_scale, const char *p_text, Vector2f p_textOffset, std::vector<const char *> p_parameters)
    : Entity(p_pos, p_tex, p_frame, Vector2f(p_scale, p_scale)), topCollider(nullptr), child(nullptr), parent(nullptr), type(p_type), text(p_text, p_pos + p_textOffset, 0.6), textOffset(p_textOffset), heightChanger(parts, 7, nullptr, 14, parameters, mainCollider, textOffset.y), parts(Vector2f(65, 14))
{
    std::cout << "Block init" << "\n";
    std::cout << p_type << "\n";
    parameters.reserve(p_parameters.size());
    parameterOffsets.reserve(p_parameters.size());
    heightChanger.parameterOffsets = &parameterOffsets;
    if (p_type != BlockType::DEFAULTHEAD)
    {
        SDL_FRect topColFrame;
        topColFrame.x = 0;
        topColFrame.y = 0;
        topColFrame.w = 32;
        topColFrame.h = 0;

        topCollider = new Collider(topColFrame, this, Collider::TOP_BLOCK);
    }

    SDL_FRect bottomColFrame;
    bottomColFrame.x = 0;
    bottomColFrame.y = 12;
    bottomColFrame.w = 32;
    bottomColFrame.h = 8;

    bottomCollider = new Collider(bottomColFrame, this, Collider::BOTTOM_BLOCK);

    if (p_type != BlockType::DEFAULTHEAD)
    {
        blocks.Add(this);

        SDL_Rect centerSize;
        centerSize.x = 14;
        centerSize.y = 4;
        centerSize.w = 48;
        centerSize.h = 6;

        if (p_type == BlockType::DEFAULTLOOP)
        {
            centerSize.x = 20;
            centerSize.w = 42;
        }
        BlockResize::InitBlockScale(
            centerSize, parts, p_scale, text, p_textOffset, parameters, p_pos, parameterOffsets, p_tex, p_parameters, heightChanger, this, true);

        mainCollider = parts.GenerateGrabbableCollider(this);

        text.getVisual() -> SetLayer(layer);

        std::cout << "Offsets pos: " << &parameterOffsets << "\n";
        std::cout << "parameters size: " << parameters.size() << "\n";
        if (parameters.size() != 0)
        {
            heightChanger.UpdateHeight();
        }

        for (auto pair : parameters)
        {
            std::cout << "update parameter layers\n";
            pair.first->getVisual()->SetLayer(layer);
            std::cout << "update other parameter\n";

            pair.second->SetLayer(layer);
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
    return GetHeadHeight();
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
    UpdateParentLoop();
}
void Block::RemoveChild()
{ 
    child->ToggleIsContained(false);
    child = nullptr;
    UpdateParentLoop();

}
void Block::MoveParameters(Vector2f p_pos)
{
    for (size_t i = 0; i < parameters.size(); ++i)
    {
        parameters[i].first->getVisual()->setPos(parameterOffsets[i].first + p_pos);

        parameters[i].second->setPos(parameterOffsets[i].second + p_pos);
    }
}
void Block::LayerParameters(int p_layer)
{
    for (auto pair : parameters)
    {
        pair.first->getVisual()->SetLayer(p_layer);

        pair.second->SetLayer(p_layer);
    }
}
void Block::setPos(Vector2f p_pos){
    pos = p_pos;
    if(child != nullptr)
    {
        child-> setPos(p_pos + Vector2f(0, (mainCollider -> GetFrame().h - 2) * scale.y));
    }
    
    parts.SetPos(p_pos);

    text.getVisual() -> setPos(p_pos + textOffset);
    MoveParameters(p_pos);
}
void Block::SetLayer(int p_layer){
    SetSelfLayer(p_layer); 
    parts.SetLayer(p_layer);

    if(child != nullptr){
        child -> SetLayer(p_layer);
    }
    text.getVisual() -> SetLayer(p_layer);

    LayerParameters(p_layer);
}
void Block::UpdateSize(){
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
}
// Add virtual function for loop that moves the bottom AND middle collider 
void Block::UpdateCollider(){
    SDL_FRect oldFrame = bottomCollider -> GetFrame();
    SDL_Rect updatedFrame = utils::InitRect(oldFrame.x, (GetHeadHeight() - pos.y - 1) / scale.y, oldFrame.w, oldFrame.h);
    bottomCollider -> SetFrame(utils::RectToFrect(updatedFrame));
    if(child != nullptr){
        child -> getPos().print();
        Vector2f(pos.x, GetHeadHeight() - scale.y).print();
        child -> setPos(Vector2f(pos.x, GetHeadHeight() - scale.y));
    }
    UpdateParentLoop();
}
float Block::GetHeadHeight(){
    return parts.bottom->getPos().y + (parts.bottom->getCurrentFrame().h - 1) * scale.y;
}
void Block::UpdateParentLoop(){
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
        it -> getParent() -> UpdateBodySize();
    }    
}
