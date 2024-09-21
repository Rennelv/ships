#include "ShipManager.hpp"

#include "Ship.hpp"

ShipManager::ShipManager() : count(0) {
}

ShipManager::ShipManager(int count, int* lengths) {
    ships.reserve(count);
    this->count = count;
    for (int i = 0; i < count; i++) {
        Ship* newShip = new Ship(lengths[i], ships.size());
        ships.push_back(newShip);
    }
}

ShipManager::~ShipManager() {
    for (int i = 0; i < count; i++) {
        delete ships[i];
    }
}

int ShipManager::getCount() {
    return count;
}

Ship* ShipManager::getShip(int index) {
    if (index == -1) {
        return ships.back();
    }
    if (index < 0 || index >= count) {
        return nullptr;
    }

    return ships[index];
}
