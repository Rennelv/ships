#ifndef BOMBARDABILITY_HPP
#define BOMBARDABILITY_HPP

#include "Abilities/Ability.hpp"
#include "ShipField.hpp"
#include "ShipManager.hpp"

class BombardAbility : public Ability {
   public:
    void use(ShipField &field, ShipManager &manager, int x, int y, AbilityResults &ret) override;
    AbilityType getType() override;
};

#endif  // BOMBARDABILITY_HPP