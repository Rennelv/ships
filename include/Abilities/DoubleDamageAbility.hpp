#ifndef DOUBLEDAMAGEABILITY_HPP
#define DOUBLEDAMAGEABILITY_HPP

#include "Abilities/Ability.hpp"

class DoubleDamageAbility : public Ability {
   public:
    void use(AbilityInput& input, AbilityResults& ret) override;
    AbilityType getType() const override;
};

#endif  // DOUBLEDAMAGEABILITY_HPP