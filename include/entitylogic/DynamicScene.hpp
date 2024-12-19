#ifndef DYNAMICSCENE_HPP
#define DYNAMICSCENE_HPP

#include "Scene.hpp"
#include "InputString.hpp"

// This class updates in a variable time step.
// This represents all of the game objects within a given scene that are not 
// effected by other player's input and thus would have no reason to be rolled back.
class DynamicScene{
    void update(float deltaTime, std::vector<Input>& frameInput, std::array<float,2>& mousePos);
};

#endif