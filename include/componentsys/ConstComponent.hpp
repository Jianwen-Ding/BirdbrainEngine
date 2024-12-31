#ifndef CONSTCOMPONENT_HPP
#define CONSTCOMPONENT_HPP

#include "Component.hpp"

/**
 * Represents component that will never change state.
 * Mostly will be made up of rendering components for RenderManger to set up.
 */
class ConstComponent : public Component<ConstComponent>{
};

#endif