#ifndef CONSTSCENE_HPP
#define CONSTSCENE_HPP

#include "Scene.hpp"

/**
 * This never calls for update. 
 * This represents objects from within the game that will never change
 * only needed for static models in the background of a fighting game that is sure to not change.
 * Prohibits changes from being made within this.
 */
class ConstScene final : public Scene{
};

#endif