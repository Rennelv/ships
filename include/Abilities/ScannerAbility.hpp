#ifndef SCANNERABILITY_HPP
#define SCANNERABILITY_HPP

#include "Abilities/Ability.hpp"
#include "ShipField.hpp"
#include "ShipManager.hpp"

class ScannerAbility : public Ability {
   public:
    void use(ShipField &field, ShipManager &manager, int x, int y, AbilityResults &ret) override;
    AbilityType getType() override;
};

#endif  // SCANNERABILITY_HPP