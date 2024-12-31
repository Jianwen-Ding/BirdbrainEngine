#ifndef INPUTFRAME_HPP
#define INPUTFRAME_HPP

#include "InputCycle.hpp"

#include <vector>

/**
 * Represents raw the input a single player makes durring one frame of game logic.
 */
struct InputFrame{
    // The vector represents the inputs within each fixed frame of gameplay.
    // The further back the input is in the first vector the later they were recorded into the frame.
    std::vector<InputCycle> inputs;

    // Checks if a certain type of input exists within the cycle.
    bool hasInput(InputID& givenInput);

    // A copy constructor for InputFrame that deep copies the original.
    InputFrame(InputFrame& original);

    // Creates an empty input frame to be added.
    InputFrame();
};

#endif