#ifndef BOMBARDABILITY_HPP
#define BOMBARDABILITY_HPP

#include "Abilities/Ability.hpp"
#include "Abilities/AbilityResults.hpp"

class BombardAbility : public Ability {
   public:
    void use(AbilityInput& input, AbilityResults& ret) override;
    AbilityType getType() const override;
};

#endif  // BOMBARDABILITY_HPP