#ifndef DYNAMICCOMPONENT_HPP
#define DYNAMICCOMPONENT_HPP

#include "Component.hpp";
#include "InputString.hpp";

// Represents a component that is dynamic but is unaffected by other player's inputs.
// Should never edit logic from Game C  mponents or Cons Components.
class DynamicComponent : Component{
    // Records all of the inputs the player made on this dynamic frame
    virtual void update(float deltaTime, std::vector<Input>& frameInput, std::array<float,2>& mousePos);
};

#endif