#pragma once

#include <SDL.h>

#include "Collider.hpp"
#include "Utils.hpp"
#include "Button.hpp"
#include "Variable.hpp"

namespace General{
    void GrabbedBlock(Block*& heldObject, SDL_Event& event, Collider*& collision, Vector2f& clickedPos);
    void GrabbedVariable(Variable*& heldVar, SDL_Event& event, Collider*& collision, Vector2f& clickedPos);
    void OnClick(SDL_Event& event, Block*& heldObject, Vector2f& clickedPos, Variable*& heldVar);
    void InsertBlock(Block*& heldObject, Block*& neighbor);
    void AttachBlock(Collider*& neighborCol, Block*& heldObject);
    void BlockReleased(Block*& heldObject);
    void VariableReleased(Variable*& heldVar);
}