#ifndef DOUBLEDAMAGEABILITY_HPP
#define DOUBLEDAMAGEABILITY_HPP

#include "Abilities/Ability.hpp"
#include "ShipField.hpp"

class DoubleDamageAbility : public Ability {
   public:
    void use(ShipField &field, int x, int y, AbilityResults &ret) override;
    AbilityType getType() override;
};

#endif  // DOUBLEDAMAGEABILITY_HPP