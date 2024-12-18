#ifndef INPUTSTRING_HPP
#define INPUTSTRING_HPP

#include "Input.hpp"

#include <vector>

// Defines a string of inputs from a single player.
struct InputString{
    // The id of the player who inputted the string
    unsigned int playerID;
    
    // Represents the actual inputs
    // The further back the out field is in the vector the newer the frame is

    // The further back the input is in the inner vector the later they were put into the frame
    std::vector<std::vector<Input>> inputs;
    // Represents the x and y coordinates of the mouse at the end of a given frame
    // [0] = x
    // [1] = y
    std::vector<std::array<int, 2>> mousePos;
};

#endif