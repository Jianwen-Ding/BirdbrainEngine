#ifndef GAMECOMPONENT_HPP
#define GAMECOMPONENT_HPP

#include "Component.hpp"
#include "InputString.hpp"
#include "Scene.hpp"

#include <vector>

class GameEntity;

/**
 * Represents objects in a game that takes in both main player and other player's inputs.
 * SHOULD NEVER INTERACT WITH CONSTANT COMPONENTS OR DYNAMIC COMPONENTS, NOR USE STATIC VARIABLES
 * otherwise rollback de-syncs are made possible and thread safety is heavily compromised.
 */
class GameComponent : public Component<GameComponent>{
    public:
        // Updates the component based on a string of inputs from all players within the game
        // Assumes a single frame represents a fixed length of time.
        virtual void update(std::vector<InputString>& inputStrings) = 0;

    protected:
        // Creates a copy of the given Game Component onto a entity.
        // The copy needs to be a deep copy of everything of pointers / references towards objects within the scene.
        // Used to help clone scene for rollbacks,
        // WILL CAUSE ROLLBACK DE-SYNCS IF NOT CORRECTLY IMPLEMENTED.
        virtual GameComponent copy(GameEntity& newBase) const = 0;
        
        friend class GameComponent;
};
#endif