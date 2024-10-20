#include "Abilities/BombardAbility.hpp"

#include <cstddef>
#include <random>

#include "ShipField.hpp"

void BombardAbility::use(ShipField& field, int, int, AbilityResults& ret) {
    // Get random segment
    std::random_device rd;   // Obtain a random number from hardware
    std::mt19937 gen(rd());  // Seed the generator
    std::uniform_int_distribution<> disX(0, field.getWidth() - 1);
    std::uniform_int_distribution<> disY(0, field.getHeight() - 1);

    int x = disX(gen);
    int y = disY(gen);

    // Check if there are any ships on the field
    bool shipFound = false;
    for (size_t i = 0; i < field.getWidth(); ++i) {
        for (size_t j = 0; j < field.getHeight(); ++j) {
            if (field.getIsShip(i, j) && field.getShipSegmentState(i, j) != ShipSegmentState::DESTROYED) {
                shipFound = true;
                break;
            }
        }
        if (shipFound) break;
    }

    if (!shipFound) {
        ret.bombardDamageDealt = false;
        return;
    }

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