#include <SDL2/SDL_image.h>

#include "Collider.hpp"

extern SDL_Texture* varTexture;

class Variable{
    public:
    Variable();
    ~Variable();
    private:
    Entity* visual;
    Collider* collision;
};