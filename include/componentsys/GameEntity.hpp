#ifndef GAMEENTITY_HPP
#endif GAMEENTITY_HPP

#include "Entity.hpp"
#include "GameComponent.hpp"

/**
 * Represents a object with the game that is effected by both main player and other player input.
 * Represents where most real gameplay will occur.
 */
class GameEntity final : Entity<GameComponent> {
    // Updates all of the components with a given input
    void update(std::vector<InputString>& inputStrings);

    // Copy constructor to be used for rollback
    GameEntity(GameEntity& original);
};