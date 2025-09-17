#pragma once

#include <unordered_map>
#include <string>

#include "Block.hpp"

class FuncHead;

extern std::unordered_map<std::string, FuncHead*> functions;

class FuncHead : public Block{
    public:
    FuncHead(Vector2f p_pos, float p_scale, SDL_Texture* p_tex, BlockType p_type, SDL_Rect p_frame, std::string p_name, Vector2f p_textOffset = Vector2f(10, 20), std::vector<const char*> p_parameters = {});
    void setPos(Vector2f p_pos) override;
};