#ifndef COMPONENT_HPP
#define COMPONENT_HPP

template <typename T>
class Entity;

/**
 * Represents a single component.
 * Represents the means onto which the logic of the game is accessed or modified from.
 * Designed to be attached to and/or removed from entities.
 * Template T represents the class that inherits off of Component.
 * Everything inherited this must have a default constructor to be attached to entities.
 */
template <typename T>
class Component{
    public:
        // What plays on the start of a scene or when a new object is instantiated.
        virtual void start() = 0;

        // Gets the entity that this component is attached to.
        Entity<T>& getEntity(){
            return baseEntity;
        }

    protected:
        // Constructs a component with a given entity.
        // It assigns the entity as it's owner but does not actually attach itself to the entity.
        Component(Entity<T>& setEntity){
            baseEntity = setEntity;
        }

        // Deattaches itself from the given entity.
        virtual ~Component() = 0;

        // The entity that the component is attached to.
        Entity<T>& baseEntity;

        friend class Entity;
};

#endif