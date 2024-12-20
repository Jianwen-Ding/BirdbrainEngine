#ifndef ENTITY_HPP
#define ENTITY_HPP

#include "Component.hpp"

#include <type_traits>
#include <vector>

/**
 * Represents a single object within a game.
 * Meant to focus the components within the given Entity.
 * Template T is the type of component that this entity updates.
 */
template <typename T, typename = std::enable_if_t<std::is_base_of<Component, T>::value>>
class Entity{
    public:
        // Gets a pointer to a component of type V within the entity.
        // Gets the most recently added component of type V.
        // Will return a nullptr if no such component exist.
        template<typename V, typename = std::enable_if_t<std::is_base_of<T, V>::value>>>
        V* getComponent();
        
        // Gets a pointer to every type component of type V within the entity.
        // Will return an empty vector if no such componenta exist.
        template<typename V, typename = std::enable_if_t<std::is_base_of<T, V>::value>>>
        std::vector<V*> getComponents();

    private:
        // List of components of a given type within the value.
        // The farther out in the vector the component 
        std::vector<T> componentVec;


        // Removes the given component from the Entity if needed, only usable by the component itself
        template<typename V, typename = std::enable_if_t<std::is_base_of<T, V>::value>>>
        bool removeComponent(V* givenComponent);

        // Only the 
        friend class Component;

};

#endif 