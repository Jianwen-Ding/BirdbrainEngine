#ifndef GAMECOMPONENT_HPP
#define GAMECOMPONENT_HPP

#include "Component.hpp"

// Represents part of the game that takes in both player and 
class GameComponent : Component{
    // Updates the component based on a string of inputs from all players within the game
    // Assumes a single frame represents a fixed length of time.
    virtual void update() = 0;

    // Creates a copy of the given Game Component
    // Used to help clone scene for rollbacks
    virtual GameComponent copy() const = 0;
};
#endif