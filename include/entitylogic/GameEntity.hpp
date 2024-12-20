#ifndef GAMEENTITY_HPP
#endif GAMEENTITY_HPP

#include "Entity.hpp"
#include "GameComponent.hpp"

/**
 * Represents a object with the game that is effected by both main player and other player input.
 * Represents where most real gameplay will occur.
 */
class GameEntity : Entity<GameComponent>{

};

#define GAMEENTITY_HPP