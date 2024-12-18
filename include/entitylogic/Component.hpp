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

        // Constructs a component 
        Component(Enitity& baseEntity);
        // Deattaches itself from the given entity
        virtual ~Component();

        // The entity that the component is attached to
        Enitity& baseEntity;
    private:

        // Allows
        void insertEntity(Enitity& givenEntity);
        friend class Entity;
        
};

#endif