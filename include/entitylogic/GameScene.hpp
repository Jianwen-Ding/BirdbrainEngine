#ifndef GAMESCENE_HPP
#define GAMESCENE_HPP

#include "InputString.hpp"

#include <vector>

// This updates itself in a fixed time step.
// This is the parts of the scene that are effected by rollback.
// This represents all objects within a scene that are effected by player input.
class GameScene{
    public:
        // Updates the given scene by one frame.
        // Inputs must lead to deterministic outcomes.
        void update(std::vector<InputString>& inputStrings);

        // Copy constructor to potentially rollback to
        GameScene(GameScene& original);
    private:
        // The amount of time that passes each frame from within a scene
        float frameTime;
};

#endif