#include "Abilities/ScannerAbility.hpp"

#include "ShipField.hpp"

void ScannerAbility::use(ShipField& field, int x, int y, AbilityResults& ret) {
    if (field.getIsShip(x, y) || field.getIsShip(x + 1, y) || field.getIsShip(x, y + 1) || field.getIsShip(x + 1, y + 1)) {
        ret.scannerShipFound = true;
    } else {
        ret.scannerShipFound = false;
    }
}

AbilityType ScannerAbility::getType() {
    return AbilityType::Scanner;
}
