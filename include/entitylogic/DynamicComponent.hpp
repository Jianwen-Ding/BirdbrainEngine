#ifndef DYNAMICCOMPONENT_HPP
#define DYNAMICCOMPONENT_HPP

#include "Component.hpp";
#include "InputString.hpp";

/**
 * Represents a component that is dynamic but is unaffected by other player's inputs.
 * SHOULD NEVER INTERACT WITH CONSTANT COMPONENTS OR GAME COMPONENTS, 
 * otherwise rollback desyncs are made possible and thread safety is heavily comprimised.
 */
class DynamicComponent : public Component{
    // Records all of the inputs the player made on this dynamic time step.
    virtual void update(float deltaTime, std::vector<Input>& frameInput, std::array<float,2>& mousePos);
};

#endif