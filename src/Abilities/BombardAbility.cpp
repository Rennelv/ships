#include "Abilities/BombardAbility.hpp"

#include <random>

#include "ShipField.hpp"
#include "ShipManager.hpp"

void BombardAbility::use(ShipField& field, ShipManager& manager, int, int, AbilityResults& ret) {
    // Check if there are any ships on the field using ShipManager
    if (manager.getAliveCount() == 0) {
        ret.bombardDamageDealt = false;
        return;
    }

    // Get random segment
    std::random_device rd;   // Obtain a random number from hardware
    std::mt19937 gen(rd());  // Seed the generator
    std::uniform_int_distribution<> disX(0, field.getWidth() - 1);
    std::uniform_int_distribution<> disY(0, field.getHeight() - 1);

    int x = disX(gen);
    int y = disY(gen);

    // Find a random segment that contains a ship
    while (!(field.getIsShip(x, y) && field.getShipSegmentState(x, y) != ShipSegmentState::DESTROYED)) {
        x = disX(gen);
        y = disY(gen);
    }

    // Apply damage to the selected segment
    field.attackShip(x, y, false, 1);
    ret.bombardDamageDealt = true;
}

AbilityType BombardAbility::getType() {
    return AbilityType::Bombard;
}