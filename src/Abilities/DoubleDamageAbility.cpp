#include "Abilities/DoubleDamageAbility.hpp"

void DoubleDamageAbility::use(AbilityInput&, AbilityResults& ret) {
    ret.DoubleDamageIsActive = true;
}

AbilityType DoubleDamageAbility::getType() const {
    return AbilityType::DoubleDamage;
}
