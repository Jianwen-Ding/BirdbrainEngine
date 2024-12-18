#ifndef DYNAMICCOMPONENT_HPP
#define DYNAMICCOMPONENT_HPP

#include "Component.hpp";
#include "InputString.hpp";

// Represents a component that is dynamic but is unaffected by other player's inputs.
class DynamicComponent : Component{
    virtual void update(float deltaTime, InputString& playerInputs);
};

#endif