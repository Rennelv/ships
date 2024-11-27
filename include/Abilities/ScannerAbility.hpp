#ifndef SCANNERABILITY_HPP
#define SCANNERABILITY_HPP

#include "Abilities/Ability.hpp"

class ScannerAbility : public Ability {
   public:
    void use(AbilityInput& input, AbilityResults& ret) override;
    AbilityType getType() const override;
};

#endif  // SCANNERABILITY_HPP