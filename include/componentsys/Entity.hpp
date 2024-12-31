#ifndef ENTITY_HPP
#define ENTITY_HPP

#include "Component.hpp"

#include <type_traits>
#include <vector>

class Scene;

/**
 * Represents a single object within a game.
 * Meant to focus the components within the given Entity.
 * Template T is the type of component that this entity updates.
 */
template <typename T>
class Entity{
    static_assert(std::is_base_of<Component<T>,T>, "Template is not inherited off of an valid component template.");

    public:
        // Gets a pointer to a component of type V within the entity.
        // Gets the most recently added component of type V.
        // Will return a nullptr if no such component exist.
        template<typename V>
        std::shared_ptr<V> getComponent(){
        }

        // Removes the given component from the Entity and deletes it.
        // Returns whether the component actually ever existed within the entity.
        template<typename V>
        bool removeComponent(std::shared_ptr<V> givenComponent){

        }

        // Attempts to adds a component of a given type into the entity and return whether successful.
        // It will fail and return false if:
        // - the the given type is not derived from T
        // - the type of component has been added before
        // - the given component doesn't have a default constructor
        template<typename V>
        bool addComponent(){
            static_assert(std::is_default_constructible<V>, "Component attempted to be added to entity does not have a valid default constructor.");
            if (std::is_base_of<T, V>::value) {
                std::shared_ptr<V> attemptGet = getComponent<V>();
                if(attemptGet == nullptr){
                    componentVec.push_back(std::make_shared<V>());
                    return true;
                }
            }
            return false;
        }


    protected:
        // Calls start on all of the components within the entity
        void start(){
            for(unsigned int componentIter = 0 ; componentIter < componentVec.size() ; componentIter++){
                // Casts to component
                std::shared_ptr<Component<T>> castBase = std::static_pointer_cast<Component<T>>(componentVec[componentIter]);
                castBase->start();
            }
        }

        // List of components of a given type within the value.
        // The farther out in the vector the component 
        std::vector<std::shared_ptr<T>> componentVec;

        // Scene that the entity is contained within
        Scene& givenScene;
        friend class Scene;
};
#endif 