#ifndef ABILITY_HPP
#define ABILITY_HPP

#include "Abilities/AbilityResults.hpp"
#include "Abilities/AbilityType.hpp"
#include "ShipField.hpp"
#include "ShipManager.hpp"

class Ability {
   public:
    virtual void use(ShipField& field, ShipManager& manager, int x, int y, AbilityResults& ret) = 0;
    virtual ~Ability() = default;
    virtual AbilityType getType() const = 0;
};

#endif  // ABILITY_HPP