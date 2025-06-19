#pragma once

#include <SDL2/SDL.h>

#include "Collider.hpp"
#include "Utils.hpp"
#include "Button.hpp"
#include "Variable.hpp"


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
    void GrabbedVariable(Variable*& heldVar, SDL_Event& event, Collider*& collision, Vector2f& clickedPos){
        
    }
    void OnClick(SDL_Event& event, Block*& heldObject, Vector2f& clickedPos, Variable*& heldVar){
        Collider* collision = utils::CheckMouseCollisions(Vector2f(event.button.x, event.button.y), {4});

        if(collision != nullptr){
            GrabbedVariable(heldVar, event, collision, clickedPos);
            return;
        }

        collision = utils::CheckMouseCollisions(Vector2f(event.button.x, event.button.y), {2});

        if(collision != nullptr){
            GrabbedBlock(heldObject, event, collision, clickedPos);
        }else{
            Collider* collision = utils::CheckMouseCollisions(Vector2f(event.button.x, event.button.y), {3});
            if(collision != nullptr){
                static_cast<Button*>(collision -> GetParent())->CallFunc();
            }
        }
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
}