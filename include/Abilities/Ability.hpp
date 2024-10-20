#ifndef ABILITY_HPP
#define ABILITY_HPP

#include "Abilities/AbilityResults.hpp"
#include "ShipField.hpp"
enum class AbilityType {
    DoubleDamage,
    Scanner,
    Bombard,
};

class Ability {
   public:
    virtual void use(ShipField& field, int x, int y, AbilityResults& ret) = 0;
    virtual ~Ability() = default;
    virtual AbilityType getType() = 0;
    virtual bool getResult() = 0;
};

#endif  // ABILITY_HPP