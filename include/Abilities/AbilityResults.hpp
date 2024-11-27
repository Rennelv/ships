#ifndef ABILITYRESULTS_HPP
#define ABILITYRESULTS_HPP

#include "ShipField.hpp"
#include "ShipManager.hpp"
struct AbilityResults {
    bool DoubleDamageIsActive = false;
    bool ScannerShipFound = false;
    bool BombardDamageDealt = false;
};

struct AbilityInput {
    ShipField &target_field;
    ShipManager &target_manager;
    int x;
    int y;
};

#endif