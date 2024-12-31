#ifndef DYNAMICCOMPONENT_HPP
#define DYNAMICCOMPONENT_HPP

#include "Component.hpp";
#include "InputCycle.hpp";

/**
 * Represents a component that is dynamic but is unaffected by other player's inputs.
 * SHOULD NEVER INTERACT WITH CONSTANT COMPONENTS OR GAME COMPONENTS, 
 * otherwise rollback de-syncs are made possible and thread safety is heavily compromised.
 */
class DynamicComponent : public Component<DynamicComponent>{
    // Records all of the inputs the player made on this dynamic time step.
    virtual void update(float deltaTime, InputCycle givenInput);
};

#endif