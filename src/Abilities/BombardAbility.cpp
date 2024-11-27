#include "Abilities/BombardAbility.hpp"

#include <random>

#include "ShipField.hpp"
#include "ShipManager.hpp"

void BombardAbility::use(AbilityInput& input, AbilityResults& ret) {
    ShipManager& manager = input.target_manager;
    ShipField& field = input.target_field;
    // Check if there are any ships on the field using ShipManager
    if (manager.getAliveCount() == 0) {
        ret.BombardDamageDealt = false;
        return;
    }

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> disX(0, field.getWidth() - 1);
    std::uniform_int_distribution<> disY(0, field.getHeight() - 1);

    int x = disX(gen);
    int y = disY(gen);

    while (!(field.getIsShip(x, y) && field.getShipSegmentState(x, y) != ShipSegmentState::DESTROYED)) {
        x = disX(gen);
        y = disY(gen);
    }

    field.attackShip(x, y, false, 1);
    ret.BombardDamageDealt = true;
}

AbilityType BombardAbility::getType() const {
    return AbilityType::Bombard;
}