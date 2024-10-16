#ifndef BOMBARDABILITY_HPP
#define BOMBARDABILITY_HPP

#include "Abilities/Ability.hpp"
#include "ShipField.hpp"

class BombardAbility : public Ability {
   public:
    void use(ShipField &field, int x, int y, AbilityResults &ret) override;
    AbilityType getType() override;
    bool getResult() override;
};

#endif  // BOMBARDABILITY_HPP