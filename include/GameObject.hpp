#ifndef GAMEOBJECT
#define GAMEOBJECT

// Standard C++
#include <iostream>
#include <list>;

// External Classes
#include "Component.hpp"

// >>PURPOSE OF CLASS<<
// The main parts of the game
// They are what controls what happens in the game and what is displayed
class GameObject{
    private:
        std::list<Component> attachedComponents;
    public:
        void insertComponent();
        // Handles creating instantiating formats (acts like prefabs in unity)
        static void instantiate();

        // >>PURPOSE OF SUPPORTING CLASS<<
        // This class functions like a prefab from unity
        // It allows for the state of a gameobject to be stored as a game object
};
#endif