#ifndef CONSTSCENE_HPP
#define CONSTSCENE_HPP

#include "Scene.hpp"

// This never calls for update.
// This represents objects from within the game that will never change
// (i.e. Constant Walls, Floors, Background Models).
// Prohibits changes from being made within this.
class ConstScene : Scene{
};

#endif