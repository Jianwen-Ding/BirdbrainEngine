#ifndef INPUTSTRING_HPP
#define INPUTSTRING_HPP

#include "Input.hpp"

#include <vector>

// Defines a string of inputs from a single player.
struct InputString{
    // The id of the player who inputted the string
    unsigned int playerID;
    
    // The first vector represents each fixed frame of gameplay
    // The further back the field is in the outer vector the newer the frame is
    // The further back the input is in the inner vector the later they were put into the frame
    std::vector<std::vector<Input>> inputs;

    // The first vector represents each fixed frame of gameplay
    // The further back the field is in the outer vector the newer the frame is
    // The further back the input is in the inner vector the later they were put into the frame
    // Represents the x and y coordinates of the mouse at the end of a given frame
    // [0] = x
    // [1] = y
    std::vector<std::vector<std::array<float, 2>>> mousePos;

    // The copy constructor of the given input string
    InputString(InputString& original);


};

#endif