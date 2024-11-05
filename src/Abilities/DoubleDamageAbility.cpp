#include "Abilities/DoubleDamageAbility.hpp"

#include "ShipField.hpp"
#include "ShipManager.hpp"

void DoubleDamageAbility::use(ShipField&, ShipManager&, int, int, AbilityResults& ret) {
    ret.doubleDamageIsActive = true;
}

AbilityType DoubleDamageAbility::getType() {
    return AbilityType::DoubleDamage;
}
