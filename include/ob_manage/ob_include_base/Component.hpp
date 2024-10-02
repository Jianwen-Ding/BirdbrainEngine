#ifndef COMPONENT
#define COMPONENT

// Standard C++
#include <iostream>
#include <list>;
#include <any>;

// External Classes
#include "GameObject.hpp"

// >>PURPOSE OF SUPPORTING CLASS<<
// This class allows gameObjects to save their state and 
struct CompFormat{
    public:
        // Paramameters of the component saved
        // On each different component list order needed to set parameters
        std::list<std::any> parameters;
};
// >>>>>>FUNCTION OF INTERFACE<<<<<<
// It is something meant to be attached to an object to modify it
// It can come in many forms like Rigidbodies, Meshes, Scripts, and Ect
class Component{
    public:
        //>>>VARS<<<
        // Whether the component has been initialized
        bool initialized;
        // Whether component is active
        bool active;
        // The gameobject attached to the component
        GameObject gameObject;

        //>>>FUNCTIONS<<<
        // Checks if component added to gameobject complies to requirements
        bool doesComply(Component& insertedComponent);
        // Initializes the component
        void initComponent(GameObject baseGameObject);
        // Initializes the component with format
        void initComponent(GameObject baseGameObject, CompFormat format);
        // Abstract function of initialization
        virtual void initComponentEffect(GameObject baseGameObject);
        // Abstract function of initialization with format
        virtual void initComponentEffect(GameObject baseGameObject, CompFormat format);
        // Creates a format of the current state of the object
        virtual void createFormat();
        // Deletes the component
        virtual void deleteComponent();
        // Sets the component to active or inactive
        virtual void setComponentActive(bool active);
        // Abstract function of setting component active/inactive
        virtual void setComponentActiveEffect(bool active);
        // Draws the component each frame
        virtual void drawComponent();
        // Draws the component each frame
        virtual void drawComponentEditor();

};

#endif