#include <unordered_set>

#include "General.hpp"

extern Vector2f cameraPos;
extern Vector2f lastCamPos;
extern bool isDragging;

namespace General{
    void GrabbedBlock(Block*& heldObject, SDL_Event& event, Collider*& collision, Vector2f& clickedPos){
        heldObject = static_cast<Block*>(collision->GetParent());
        clickedPos = Vector2f(event.button.x - heldObject -> getPos().x, event.button.y - heldObject -> getPos().y);
        if(heldObject -> getParent() != nullptr){
            if(heldObject -> getParent() -> GetType() == BlockType::DEFAULTLOOP){
                heldObject -> getParent() -> RemoveChild(heldObject);
            }
            else{
                heldObject -> getParent() -> RemoveChild();
            }
            heldObject -> setParent(nullptr);
        }
        heldObject -> SetLayer(2);
    }

    void GrabbedVariable(Variable*& heldVar, SDL_Event& event, Collider*& collision, Vector2f& clickedPos)
    {
        heldVar = static_cast<Variable*>(collision->GetParent());
        clickedPos = Vector2f(event.button.x - heldVar -> getPos().x, event.button.y - heldVar -> getPos().y);
        heldVar -> SetLayer(2);
        if(heldVar -> GetParent() != nullptr){
            heldVar -> GetParent() -> Detach();
            heldVar -> SetParent(nullptr);
        }
    }

    void OnClick(SDL_Event& event, Block*& heldObject, Vector2f& clickedPos, Variable*& heldVar, TextArea*& selectedTextBox){
        Collider* collision = utils::CheckMouseCollisions(Vector2f(event.button.x, event.button.y) + cameraPos, {Collider::GRABBABLE_VAR});
        if(collision != nullptr){
            GrabbedVariable(heldVar, event, collision, clickedPos);
            collision = utils::CheckMouseCollisions(Vector2f(event.button.x, event.button.y) + cameraPos, {Collider::TEXT_AREA});
            if(collision != nullptr){
                selectedTextBox = (TextArea*)collision->GetParent();
            }
            return;
        }
        collision = utils::CheckMouseCollisions(Vector2f(event.button.x, event.button.y) + cameraPos, {Collider::GRABBABLE});
        if(collision != nullptr){
            GrabbedBlock(heldObject, event, collision, clickedPos);
            return;
        }
        else{
            collision = utils::CheckMouseCollisions(Vector2f(event.button.x, event.button.y) + cameraPos, {Collider::BUTTON});
            if(collision != nullptr){
                static_cast<Button*>(collision -> GetParent())->CallFunc();
                return;
            }
        }
        beginDragging(clickedPos, event);
        selectedTextBox = nullptr;
    }
    void beginDragging(Vector2f& clickedPos, SDL_Event& event){
        lastCamPos = cameraPos;
        clickedPos = Vector2f(event.button.x, event.button.y);
        isDragging = true;
    }
    void InsertBlock(Block*& heldObject, Block*& neighbor){
        Block* iterator = heldObject;
        while(iterator -> getChild() != nullptr){
            iterator = iterator -> getChild();
        }
        iterator -> setChild(neighbor -> getChild());
        iterator -> getChild() -> setParent(iterator);
    }

    void AttachBlock(Collider*& neighborCol, Block*& heldObject){
        Block* neighbor = static_cast<Block*>(neighborCol -> GetParent());
        if(neighbor -> getChild() != nullptr){
            //Verifies that it isn't the inside of the loop reacting to the children of the entire loop.
            if(neighborCol == &(neighbor -> getBottomCollider())){
                InsertBlock(heldObject, neighbor);
            }
        }
        heldObject -> setPos(neighbor -> getPos() + Vector2f(neighborCol -> GetFrame().x * neighbor -> getScale().x, neighborCol -> GetFrame().y * neighbor  -> getScale().y));
        if(neighbor -> GetType() == BlockType::DEFAULTLOOP){
            neighbor -> setChild(heldObject, neighborCol);
        }
        else{
            neighbor -> setChild(heldObject);
        }
        heldObject -> setParent(neighbor);
    }

    void BlockReleased(Block*& heldObject){
        Collider* neighborCol;
        if(heldObject -> GetType() != BlockType::DEFAULTHEAD){
            neighborCol = heldObject -> getTopCollider() -> CheckForCollisionsHeightPriority({1});
            if(neighborCol != nullptr){
                AttachBlock(neighborCol, heldObject);
            }
        }
        heldObject -> SetLayer(0);
        heldObject = nullptr;
    }

    void VariableReleased(Variable*& heldVar){
        heldVar -> SetLayer(0);
        Collider* neighborCol;
        std::unordered_set<void*> myGaps;
        heldVar -> trackOwnParameters(myGaps);
        auto predicate = [myGaps](Collider* col) -> bool {return (myGaps.find(col -> GetParent()) != myGaps.end());};
        neighborCol = heldVar -> GetCollider() -> CheckForCollisions({5}, predicate);
        if(neighborCol != nullptr){
            static_cast<Gap*>(neighborCol -> GetParent()) -> SetAttached(heldVar);
        }
        heldVar = nullptr;
    }
}
