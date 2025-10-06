#include <algorithm>

#include "HeightChanger.hpp"
#include "Gap.hpp"

const int TEXT_HEIGHT = 16;

void HeightChanger::UpdateHeight(){
    std::cout << "updating height\n";
    std::vector<int> argumentHeights = GetArgumentHeights();

    int height = *std::max_element(argumentHeights.begin(), argumentHeights.end());

    height += baseHeight * parts.top -> getScale().y;
    height = std::max(height, (int)(minHeight * parts.top -> getScale().y));

    if(parent != nullptr){
        parent -> UpdateHeight();
    }

    height -= parts.top -> getCurrentFrame().h * parts.top -> getScale().y;
    height -= parts.bottom -> getCurrentFrame().h * parts.bottom -> getScale().y;

    parts.left -> setScale(Vector2f(parts.left -> getScale().x, height / parts.left -> getCurrentFrame().h));
    parts.center -> setScale(Vector2f(parts.center -> getScale().x, parts.left -> getScale().y));
    parts.right -> setScale(parts.left -> getScale());
    
    parts.bottomLeft -> setPos(parts.left -> getPos() + Vector2f(0, parts.left -> getCurrentFrame().h * parts.left -> getScale().y));
    parts.bottom -> setPos(Vector2f(parts.bottom->getPos().x, parts.bottomLeft -> getPos().y));
    parts.bottomRight -> setPos(Vector2f(parts.bottomRight->getPos().x, parts.bottomLeft -> getPos().y));

    col -> SetFrame(parts.GetFullRect());

    
    textOffsetY = parts.GetFullRect().h * parts.topRight->getScale().y / 2 - TEXT_HEIGHT;
    std::cout << "Offsets pos: " << &parameterOffsets << "\n";

    std::cout << "offsets size: " << parameterOffsets -> size() << "\n";
    for(int i = 0; i < parameterOffsets -> size(); ++i){
        (*parameterOffsets)[i].first.y = textOffsetY;
        (*parameterOffsets)[i].second.y = textOffsetY;
    }

}
std::vector<int> HeightChanger::GetArgumentHeights(){
    std::vector<int> res(parameters.size());
    for(size_t i = 0; i < parameters.size(); ++i){
        res[i] = parameters[i].second -> GetHeight();
    }
    return res;
}
