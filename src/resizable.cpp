#include "Resizable.hpp"

namespace BlockResize{
    void InitBlockScale(SDL_Rect& p_frame, SDL_Rect& p_topFrame, SDL_Rect& p_topRightFrame, SDL_Rect& p_leftFrame, 
                        SDL_Rect& p_centerFrame, SDL_Rect& p_rightFrame, SDL_Rect& p_bottomLeftFrame,
                        SDL_Rect& p_bottomFrame, SDL_Rect& p_bottomRightFrame, DividedEntity& p_parts, float p_scale, 
                        TextBox& p_text, Vector2f& p_textOffset, std::vector<std::pair<TextBox*, Gap*>>& p_outParameters, 
                        Vector2f& p_pos, std::vector<std::pair<Vector2f, Vector2f>>& p_parameterOffsets, SDL_Texture* p_tex,
                        std::vector<const char*> p_inParameters, Block* p_identity)
    {
        float a = p_frame.w * p_scale;
        float b = p_text.getDimensions().x + p_textOffset.x * 2;
        float c = p_topRightFrame.w * p_scale;

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


        p_parts.top = new Entity(Vector2f(a + p_pos.x, p_pos.y), p_tex, p_topFrame,  (a < b - c) ? Vector2f((b - a - c) / p_topFrame.w, p_scale) : Vector2f(0, 0));

        p_parts.topRight = new Entity(Vector2f(((a < b - c) ? b - c : a) + p_pos.x, p_pos.y), p_tex, p_topRightFrame, Vector2f(p_scale, p_scale));

        Vector2f topMargin(0, p_leftFrame.y * p_scale);

        p_parts.left = new Entity(p_pos + topMargin, p_tex, p_leftFrame, Vector2f(p_scale, p_scale));

        p_parts.center = new Entity(p_parts.top -> getPos() + topMargin, p_tex, p_centerFrame, p_parts.top -> getScale());

        p_parts.right = new Entity(p_parts.topRight -> getPos() + topMargin, p_tex, p_rightFrame, Vector2f(p_scale, p_scale));

        topMargin.y = p_bottomLeftFrame.y * p_scale;

        p_parts.bottomLeft = new Entity(p_pos + topMargin, p_tex, p_bottomLeftFrame, Vector2f(p_scale, p_scale));

        p_parts.bottom = new Entity(p_parts.top -> getPos() + topMargin, p_tex, p_bottomFrame, p_parts.top -> getScale());

        p_parts.bottomRight = new Entity(p_parts.topRight -> getPos() + topMargin, p_tex, p_bottomRightFrame, Vector2f(p_scale, p_scale));
    }
    void UpdateBlockScale(
        SDL_Rect& p_currentFrame, TextBox& p_text, Vector2f& p_scale,
        Vector2f& p_textOffset, std::vector<std::pair<TextBox*, Gap*>>& p_parameters,
        std::vector<std::pair<Vector2f, Vector2f>>& p_parameterOffsets,
        Vector2f& p_pos, DividedEntity& p_parts
    )
    {
        float a = p_currentFrame.w * p_scale.x;
        float b = p_text.getDimensions().x + p_textOffset.x * 2;
        float c = p_parts.topRight -> getCurrentFrame().w * p_scale.x;

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

        p_parts.top -> setPos(Vector2f(a + p_pos.x, p_pos.y)); 
        p_parts.top -> setScale(Vector2f((b - a - c) / p_parts.top -> getCurrentFrame().w, p_scale.y));

        p_parts.topRight -> setPos(Vector2f(((a < b - c) ? b - c : a) + p_pos.x, p_pos.y));

        p_parts.center -> setPos(Vector2f(p_parts.top -> getPos().x, p_parts.center -> getPos().y));
        p_parts.center -> setScale(p_parts.top -> getScale());

        p_parts.right -> setPos(Vector2f(p_parts.topRight -> getPos().x, p_parts.right -> getPos().y));

        p_parts.bottom -> setPos(Vector2f(p_parts.top -> getPos().x, p_parts.bottom -> getPos().y));
        p_parts.bottom -> setScale(p_parts.top -> getScale());

        p_parts.bottomRight -> setPos(Vector2f(p_parts.topRight -> getPos().x, p_parts.bottomRight -> getPos().y));
    }
}