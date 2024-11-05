#ifndef DOUBLEDAMAGEABILITY_HPP
#define DOUBLEDAMAGEABILITY_HPP

#include "Abilities/Ability.hpp"
#include "ShipField.hpp"
#include "ShipManager.hpp"

class DoubleDamageAbility : public Ability {
   public:
    void use(ShipField &field, ShipManager &manager, int x, int y, AbilityResults &ret) override;
    AbilityType getType() override;
};

#endif  // DOUBLEDAMAGEABILITY_HPP