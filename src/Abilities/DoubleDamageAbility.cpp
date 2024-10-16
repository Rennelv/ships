#include "Abilities/DoubleDamageAbility.hpp"

#include "ShipField.hpp"

void DoubleDamageAbility::use([[maybe_unused]] ShipField& field, int, int, AbilityResults& ret) {
    ret.doubleDamageIsActive = true;
}

AbilityType DoubleDamageAbility::getType() {
    return AbilityType::DoubleDamage;
}

bool DoubleDamageAbility::getResult() {
    return true;
}