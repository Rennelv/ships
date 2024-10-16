#include "Player.hpp"

Player::Player() {
    size_t lengths[] = {4, 3, 2, 2, 1, 1};
    shipManager = std::make_unique<ShipManager>(6, lengths);
    abilityManager = std::make_unique<AbilityManager>();
    field = std::make_unique<ShipField>(10, 10);
}