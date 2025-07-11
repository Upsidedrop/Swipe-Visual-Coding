#include "Resizable.hpp"

namespace BlockResize{
    void InitBlockScale(SDL_Rect& p_frame, SDL_Rect& p_middleFrame, SDL_Rect& p_endFrame, float p_scale, 
                        TextBox& p_text, Vector2f& p_textOffset, std::vector<std::pair<TextBox*, Gap*>>& p_outParameters,
                        Vector2f& p_pos, std::vector<std::pair<Vector2f, Vector2f>>& p_parameterOffsets, SDL_Texture* p_tex,
                        std::vector<const char*> p_inParameters, Block* p_identity, Entity*& p_middle, Entity*& p_end)
    {
        float a = p_frame.w * p_scale;
        float b = p_text.getDimensions().x + p_textOffset.x * 2;
        float c = p_endFrame.w * p_scale;

        for(size_t i = 0; i < p_inParameters.size(); ++i){
            p_outParameters.push_back(std::make_pair(nullptr, nullptr));
            p_parameterOffsets.push_back(std::make_pair(Vector2f(0,0), Vector2f(0,0)));
            
            p_outParameters[i].first = new TextBox(p_inParameters[i], Vector2f(b, p_textOffset.y) + p_pos, p_text.getScale());

            //Saving offset for later so it doesnt need to be recalculated all the time
            p_parameterOffsets[i].first = Vector2f(b, p_textOffset.y);
            b += p_outParameters[i].first -> getDimensions().x + p_textOffset.x;
            
            p_outParameters[i].second = new Gap(Vector2f(b, p_textOffset.y) + p_pos, p_identity);
            //Saving offset for later so it doesnt need to be recalculated all the time
            p_parameterOffsets[i].second = Vector2f(b, p_textOffset.y);
            b += p_outParameters[i].second -> GetSize() * p_scale + p_textOffset.x;
        }

        p_middle = (a < b - c) ? new Entity(Vector2f(a + p_pos.x, p_pos.y), p_tex, p_middleFrame, Vector2f((b - a - c) / p_middleFrame.w, p_scale)) : nullptr;

        p_end = new Entity(Vector2f(((a < b - c) ? b - c : a) + p_pos.x, p_pos.y), p_tex, p_endFrame, Vector2f(p_scale, p_scale));
        
    }
    void UpdateBlockScale(
        SDL_Rect& p_currentFrame, TextBox& p_text, Vector2f& p_scale,
        Vector2f& p_textOffset, std::vector<std::pair<TextBox*, Gap*>>& p_parameters,
        std::vector<std::pair<Vector2f, Vector2f>>& p_parameterOffsets,
        Vector2f& p_pos, Entity* p_middle, Entity* p_end
    )
    {
        float a = p_currentFrame.w * p_scale.x;
        float b = p_text.getDimensions().x + p_textOffset.x * 2;
        float c = p_end -> getCurrentFrame().w * p_scale.x;

        for(size_t i = 0; i < p_parameters.size(); ++i){        
            p_parameters[i].first -> getVisual() -> setPos(Vector2f(b, p_textOffset.y) + p_pos);
            //Saving offset for later so it doesnt need to be recalculated all the time
            p_parameterOffsets[i].first = Vector2f(b, p_textOffset.y);
            b += p_parameters[i].first -> getDimensions().x + p_textOffset.x;

            p_parameters[i].second -> setPos(Vector2f(b, p_textOffset.y) + p_pos);
            //Saving offset for later so it doesnt need to be recalculated all the time
            p_parameterOffsets[i].second = Vector2f(b, p_textOffset.y);
            b += p_parameters[i].second -> GetSize() * p_scale.x + p_textOffset.x;
        }

        p_middle -> setPos(Vector2f(a + p_pos.x, p_pos.y)); 
        p_middle -> setScale(Vector2f((b - a - c) / p_middle -> getCurrentFrame().w, p_scale.y));

        p_end -> setPos(Vector2f(((a < b - c) ? b - c : a) + p_pos.x, p_pos.y));
    }
}