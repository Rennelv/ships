#ifndef SCANNERABILITY_HPP
#define SCANNERABILITY_HPP

#include "Abilities/Ability.hpp"
#include "ShipField.hpp"

class ScannerAbility : public Ability {
   public:
    void use(ShipField &field, int x, int y, AbilityResults &ret) override;
    AbilityType getType() override;
};

#endif  // SCANNERABILITY_HPP