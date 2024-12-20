#ifndef SCENE_HPP
#define SCENE_HPP

#include "Entity.hpp"

#include <type_traits>

/**
 * An abstract class for scene that handles the storing of objects within a game.
 * Template is the type of entity the scene stores.
 */
//template <typename T, std::enable_if_t<std::is_base_of_v<Entity, T>>>

class Scene{
    
};

#endif