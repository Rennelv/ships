#include "Abilities/ScannerAbility.hpp"

#include "ShipField.hpp"
#include "ShipManager.hpp"

void ScannerAbility::use(ShipField& field, ShipManager&, int x, int y, AbilityResults& ret) {
    int scanner_range = 1;
    if (field.getIsShip(x, y) || field.getIsShip(x + scanner_range, y) || field.getIsShip(x, y + scanner_range) ||
        field.getIsShip(x + scanner_range, y + scanner_range)) {
        ret.ScannerShipFound = true;
    } else {
        ret.ScannerShipFound = false;
    }
}

AbilityType ScannerAbility::getType() const {
    return AbilityType::Scanner;
}
