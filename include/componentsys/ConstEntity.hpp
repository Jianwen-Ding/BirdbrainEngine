#ifndef CONSTENTITY_HPP
#define CONSTENTITY_HPP

#include "Entity.hpp"
#include "ConstComponent.hpp"
/**
 * An entity that holds const components and should never change state.
 */
class ConstEntity final : Entity<ConstComponent>{
};

#endif