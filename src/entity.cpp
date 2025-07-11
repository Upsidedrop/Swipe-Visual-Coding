#include "Entity.hpp"

Entity::Entity(Vector2f p_pos, SDL_Texture* p_tex, SDL_Rect p_frame, Vector2f p_scale, int p_layer)
:pos(p_pos), scale(p_scale), currentFrame(p_frame), tex(p_tex)
{
    layer = p_layer;
    auto it = layers.find(p_layer); 
    if(it == layers.end()){
        layers.insert(std::make_pair(layer, std::unordered_set<Entity*>()));
        it = layers.find(layer); 
    }

    it -> second.insert(this);
}
SDL_Texture* Entity::getTex(){
    return tex;
}
SDL_Rect Entity::getCurrentFrame(){
    return currentFrame;
}
void Entity::SetLayer(int p_layer){
    layers.find(layer) -> second.erase(this);

    layer = p_layer;

    auto it = layers.find(layer);
    if(it == layers.end()){
        layers.insert(std::make_pair(layer, std::unordered_set<Entity*>()));
        it = layers.find(layer); 
    }
    layers.find(layer) -> second.insert(this);
}