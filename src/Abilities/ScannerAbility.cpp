#include "Abilities/ScannerAbility.hpp"

#include "ShipField.hpp"
#include "ShipManager.hpp"

void ScannerAbility::use(ShipField& field, ShipManager&, int x, int y, AbilityResults& ret) {
    int scannerRange = 1;
    if (field.getIsShip(x, y) || field.getIsShip(x + scannerRange, y) || field.getIsShip(x, y + scannerRange) ||
        field.getIsShip(x + scannerRange, y + scannerRange)) {
        ret.scannerShipFound = true;
    } else {
        ret.scannerShipFound = false;
    }
}

AbilityType ScannerAbility::getType() {
    return AbilityType::Scanner;
}
