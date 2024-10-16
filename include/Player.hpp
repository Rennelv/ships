#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <memory>

#include "Abilities/AbilityManager.hpp"
#include "ShipField.hpp"
#include "ShipManager.hpp"
class Player {
    std::unique_ptr<ShipManager> shipManager;
    std::unique_ptr<ShipField> field;
    std::unique_ptr<AbilityManager> abilityManager;

   public:
    Player();
    ~Player();
};

#endif  // PLAYER_HPP