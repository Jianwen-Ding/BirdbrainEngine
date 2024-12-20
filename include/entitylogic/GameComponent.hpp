#ifndef GAMECOMPONENT_HPP
#define GAMECOMPONENT_HPP

#include "Component.hpp"

/**
 * Represents objects in a game that takes in both main player and other player's inputs.
 * SHOULD NEVER INTERACT WITH CONSTANT COMPONENTS OR DYNAMIC COMPONENTS, 
 * otherwise rollback desyncs are made possible and thread safety is heavily comprimised.
 */
class GameComponent : public Component{
    // Updates the component based on a string of inputs from all players within the game
    // Assumes a single frame represents a fixed length of time.
    virtual void update() = 0;

    // Creates a copy of the given Game Component
    // Used to help clone scene for rollbacks
    virtual GameComponent copy() const = 0;
};
#endif