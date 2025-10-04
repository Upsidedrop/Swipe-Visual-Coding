#include "Variable.hpp"
#include "Utils.hpp"
#include "Resizable.hpp"

Variable::Variable(Vector2f p_pos, SDL_Texture *p_tex, const char *p_text, Vector2f p_textOffset, float p_scale, int p_layer, std::vector<const char *> p_parameters)
    : Entity(p_pos, p_tex, utils::InitRect(0, 0, 3, 3), Vector2f(p_scale, p_scale), p_layer), parent(nullptr), textOffset(p_textOffset), text(p_text, p_pos + p_textOffset, 0.6), heightChanger(parts, 7, nullptr, 7, parameters, collision, textOffset.y), parts(Vector2f(10, 7))
{
    SDL_Rect centerTexSize = utils::InitRect(3, 3, 4, 1);
    
    parameters.reserve(p_parameters.size());
    parameterOffsets.reserve(p_parameters.size());
    heightChanger.parameterOffsets = &parameterOffsets;
    BlockResize::InitBlockScale(centerTexSize, parts, p_scale, text, p_textOffset, parameters, p_pos, parameterOffsets, p_tex, p_parameters, heightChanger, this, false);

    collision = parts.GenerateGrabbableCollider(this, 4);

    if (parameters.size() != 0)
    {
        heightChanger.UpdateHeight();
    }
    setPos(pos);
}
Variable::~Variable()
{
    delete collision;
}
Collider *Variable::GetCollider()
{
    return collision;
}
void Variable::SetParent(Gap *p_parent)
{
    parent = p_parent;
}
Gap *Variable::GetParent()
{
    return parent;
}
float Variable::GetSize()
{
    return collision->GetFrame().w;
}
void Variable::MoveParameters(Vector2f p_pos)
{
    for (size_t i = 0; i < parameters.size(); ++i)
    {
        parameters[i].first->getVisual()->setPos(parameterOffsets[i].first + p_pos);

        parameters[i].second->setPos(parameterOffsets[i].second + p_pos);
    }
}
void Variable::LayerParameters(int p_layer)
{
    for (auto pair : parameters)
    {
        pair.first->getVisual()->SetLayer(p_layer + 1);

        pair.second->SetLayer(p_layer + 1);
    }
}
float Variable::GetHeight()
{
    return collision->GetFrame().h * parts.topRight -> getScale().y;
}
void Variable::setPos(Vector2f p_pos){
    pos = p_pos;

    parts.SetPos(p_pos);

    text.getVisual() -> setPos(p_pos + textOffset);
    MoveParameters(p_pos);
    p_pos.print();
}
void Variable::SetLayer(int p_layer){
    parts.SetLayer(p_layer);

    text.getVisual() -> SetLayer(p_layer + 1);

    LayerParameters(p_layer);

    layer = p_layer;
    
    auto it = layers.find(layer);
    if(it == layers.end()){
        layers.insert(std::make_pair(layer, std::unordered_set<Entity*>()));
        it = layers.find(layer); 
    }
    layers.find(layer) -> second.insert(this);
}
DividedEntity& Variable::GetParts(){
    return parts;
}
void Variable::UpdateSize(){
    BlockResize::UpdateBlockScale(
        currentFrame, text, scale,
        textOffset, parameters,
        parameterOffsets,
        pos, parts
    );
    collision -> SetFrame(parts.GetFullRect());
    if(parent != nullptr){
    	parent -> UpdateSize();
    }
}
