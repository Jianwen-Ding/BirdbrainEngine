#ifndef COMPONENT_HPP
#define COMPONENT_HPP

class Entity;

// Represents a single component.
// Represents the means onto which the actual logic of the game is accessed or modified from.
class Component{
    public:
        // What plays on the start of a scene or when a new object is instantiated
        void start();

        // 
        Enitity& getEntity();
    protected:

        // Constructs a component with a given entity.
        // It assigns the entity as it's owner but does not actually attach itself to the entity
        Component(Enitity& baseEntity);
        // Deattaches itself from the given entity
        virtual ~Component();

        // The entity that the component is attached to
        Enitity& baseEntity;
        friend class Entity;
        
};

#endif