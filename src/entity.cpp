#include "Entity.hpp"

Entity::Entity(Vector2f p_pos, SDL_Texture* p_tex, SDL_Rect p_frame, Vector2f p_scale, int p_layer)
:pos(p_pos), scale(p_scale), currentFrame(p_frame), tex(p_tex), enabled(true)
{
    layer = p_layer;

    auto it = layers.find(layer);
    if(it == layers.end()){
        layers.insert(std::make_pair(layer, new RandomDeletionStack<Entity*>(nullptr)));
        it = layers.find(layer); 
    }
    it -> second -> Push(this);
}
SDL_Texture* Entity::getTex(){
    return tex;
}
void Entity::setTex(SDL_Texture* p_tex){
    tex = p_tex;
}
void Entity::setFrame(SDL_Rect p_frame){
    currentFrame = p_frame;
}
SDL_Rect Entity::getCurrentFrame(){
    return currentFrame;
}
void Entity::SetLayer(int p_layer){
    SetSelfLayer(p_layer);
}
void Entity::SetSelfLayer(int p_layer){
    {
        auto oldLayer = layers.find(layer); 
        auto newLast = oldLayer -> second -> DeleteElement(this);
        if(newLast != nullptr){
            oldLayer -> second -> SetLast(newLast); 
        }
    }
    
    layer = p_layer;

    auto it = layers.find(layer);
    if(it == layers.end()){
        layers.insert(std::make_pair(layer, new RandomDeletionStack<Entity*>(nullptr)));
        it = layers.find(layer); 
    }
    it -> second -> Push(this);

}
