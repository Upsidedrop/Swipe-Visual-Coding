#include "Variable.hpp"
#include "Utils.hpp"
#include "Resizable.hpp"

Variable::Variable(Vector2f p_pos, SDL_Texture *p_tex, const char *p_text, Vector2f p_textOffset, float p_scale, int p_layer, std::vector<const char *> p_parameters)
    : Entity(p_pos, p_tex, utils::InitRect(0, 0, 3, 3), Vector2f(p_scale, p_scale), p_layer), parent(nullptr), textOffset(p_textOffset), text(p_text, p_pos + p_textOffset, 0.6), heightChanger(parts, 7, nullptr, 7, parameters, collision), parts(Vector2f(10, 7))
{
    SDL_Rect centerTexSize = utils::InitRect(3, 3, 4, 1);
    BlockResize::InitBlockScale(centerTexSize, parts, p_scale, text, p_textOffset, parameters, p_pos, parameterOffsets, p_tex, p_parameters, heightChanger, this, false);

    collision = parts.GenerateGrabbableCollider(this, 4);

    if (parameters.size() != 0)
    {
        heightChanger.UpdateHeight();
    }
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