#pragma once

#include "Utils.hpp"
#include "Entity.hpp"
#include "Block.hpp"
#include "Math.hpp"

class Loop : public Block{
    const int TOTAL_TEXTURE_HEIGHT = 21;

    public:
    Loop(Vector2f p_pos, float p_scale, SDL_Texture* p_tex, BlockType p_type , SDL_Rect p_frame, const char* p_text = "Hello World!", Vector2f p_textOffset = Vector2f(10, 9), std::vector<const char*> p_parameters = {});
    ~Loop();
    Collider* GetInnerCollider(){
        return innerCollider;
    }
    void setPos(Vector2f p_pos) override;
    float GetBottom() override;
    void SetLayer(int p_layer) override;
    Block* GetInnerChild(){
        return innerChild;
    }
    void setChild(Block* p_child, Collider* p_col) override;
    void setBodySize(float p_size) override;
    void RemoveChild(Block* p_child) override;
    void UpdateSize() override;
    void UpdateBodyPos();
    void UpdateCollider() override;
    private:
    Entity* body;
    Entity* foot;
    Collider* innerCollider;
    Block* innerChild;
    uint bodySize;
    Entity* footMiddle;
    Entity* footEnd;
};
