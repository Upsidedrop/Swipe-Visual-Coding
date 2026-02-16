#include "Variable.hpp"
#include "Utils.hpp"
#include "Resizable.hpp"

LinkedList<Variable> Variable::vars;

Variable::Variable(Vector2f p_pos, SDL_Texture *p_tex, const char *p_text, Vector2f p_textOffset, float p_scale, int p_layer, std::vector<const char *> p_parameters, VarCommand p_command)
    : Entity(p_pos, p_tex, utils::InitRect(0, 0, 3, 3), Vector2f(p_scale, p_scale), p_layer), parent(nullptr), textOffset(p_textOffset), text(p_text, p_pos + p_textOffset, 0.6), heightChanger(parts, 7, nullptr, 7, parameters, collision, textOffset.y), parts(Vector2f(10, 7)), command(p_command)
{
    vars.Add(this);

    SDL_Rect centerTexSize = utils::InitRect(3, 3, 4, 1);
    
    parameters.reserve(p_parameters.size());
    parameterOffsets.reserve(p_parameters.size());
    heightChanger.parameterOffsets = &parameterOffsets;
    BlockResize::InitBlockScale(centerTexSize, parts, p_scale, text, p_textOffset, parameters, p_pos, parameterOffsets, p_tex, p_parameters, heightChanger, this, false);

    text.getVisual() -> SetLayer(layer);

    collision = parts.GenerateGrabbableCollider(this, Collider::GRABBABLE_VAR);

    if (parameters.size() != 0)
    {
        heightChanger.UpdateHeight();
    }

    for (auto pair : parameters)
    {
        pair.first->getVisual()->SetLayer(layer);

        pair.second->SetLayer(layer);
    }

    setPos(pos);
}
VarCommand Variable::getCommand(){
    return command;
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
        pair.first->getVisual()->SetLayer(p_layer);

        pair.second->SetLayer(p_layer);
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
}
void Variable::SetLayer(int p_layer){
    SetSelfLayer(p_layer);

    parts.SetLayer(p_layer);

    text.getVisual() -> SetLayer(p_layer);

    LayerParameters(p_layer);
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
void Variable::trackOwnParameters(std::unordered_set<void*>& p_set){
    for(auto pair : parameters){
        p_set.insert(pair.second);
        if(pair.second -> getAttached() == nullptr){
            continue;
        }
        pair.second -> getAttached() -> trackOwnParameters(p_set);;
    }
}
bool Variable::hasText() {
    return false;
}
std::string Variable::getText(){
    return text.getText();
}
Gap* Variable::getParam(int index){
    return parameters[index].second;
}
