#include "Entity.hpp"
#include "Math.hpp"

class Loop{
    public:
    Loop(Vector2f p_pos, Vector2f p_scale, SDL_Texture* p_tex, std::map<int, std::unordered_set<Entity*>>* p_layers);
    ~Loop();
    private:
    Vector2f pos;
    Vector2f scale;
    Entity* head;
    Entity* body;
    Entity* foot;
};