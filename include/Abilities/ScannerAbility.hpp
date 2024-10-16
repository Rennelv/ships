#ifndef SCANNERABILITY_HPP
#define SCANNERABILITY_HPP

#include "Abilities/Ability.hpp"
#include "ShipField.hpp"

class ScannerAbility : public Ability {
   private:
    bool result;

   public:
    void use(ShipField &field, int x, int y, AbilityResults &ret) override;
    AbilityType getType() override;
    bool getResult() override;
};

#endif  // SCANNERABILITY_HPP