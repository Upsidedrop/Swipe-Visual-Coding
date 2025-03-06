#include "Entity.hpp"

Entity::Entity(Vector2f p_pos, SDL_Texture* p_tex, std::map<int, std::unordered_set<Entity*>>* p_layers, Vector2f p_scale, uint p_w, uint p_h)
:layers(p_layers), pos(p_pos), scale(p_scale), tex(p_tex)
{
    auto it = p_layers -> find(0); 
    if(it == p_layers -> end()){
        p_layers -> insert(std::make_pair(0, std::unordered_set<Entity*>()));
        it = p_layers -> find(0); 
    }

    it -> second.insert(this);

    currentFrame.x = 0;
    currentFrame.y = 0;
    currentFrame.w = p_w;
    currentFrame.h = p_h;
}
SDL_Texture* Entity::getTex(){
    return tex;
}
SDL_Rect Entity::getCurrentFrame(){
    return currentFrame;
}
void Entity::SetLayer(int p_layer){
    std::cout << layers -> find(layer) -> second.erase(this) << std::endl;

    layer = p_layer;

    auto it = layers -> find(layer);
    if(it == layers -> end()){
        layers -> insert(std::make_pair(layer, std::unordered_set<Entity*>()));
        it = layers -> find(layer); 
    }
    layers -> find(layer) -> second.insert(this);
}