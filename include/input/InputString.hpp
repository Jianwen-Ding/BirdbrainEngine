#ifndef INPUTSTRING_HPP
#define INPUTSTRING_HPP

#include "InputFrame.hpp"

#include <vector>

/**
 * Defines a string of inputs from a single player.
 */
struct InputString{
    // The id of the player who inputted the string
    unsigned int playerID;
    
    // The later the frame, the later the 
    std::vector<InputFrame> inputs;

    // The copy constructor of the given input string
    InputString(InputString& original);
};

#endif