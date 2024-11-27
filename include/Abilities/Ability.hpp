#ifndef ABILITY_HPP
#define ABILITY_HPP

#include "Abilities/AbilityResults.hpp"
#include "Abilities/AbilityType.hpp"

class Ability {
   public:
    virtual void use(AbilityInput& input, AbilityResults& ret) = 0;
    virtual ~Ability() = default;
    virtual AbilityType getType() const = 0;
};

#endif  // ABILITY_HPP