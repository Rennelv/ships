#include "ShipManager.hpp"

#include "Ship.hpp"

ShipManager::ShipManager() : ships_count(0) {
}

ShipManager::ShipManager(int count, int* lengths) {
    ships.reserve(count);
    ships_count = count;
    for (int i = 0; i < ships_count; i++) {
        Ship* newShip = new Ship(lengths[i], ships.size());
        ships.push_back(newShip);
    }
}

ShipManager::~ShipManager() {
    for (int i = 0; i < ships_count; i++) {
        delete ships[i];
    }
}

int ShipManager::getCount() {
    return ships_count;
}

int ShipManager::getAliveCount() {
    int alive = 0;
    for (int i = 0; i < ships_count; i++) {
        if (ships[i]->isAlive()) {
            alive++;
        }
    }
    return alive;
}

Ship* ShipManager::getShip(int index) {
    if (index == -1) {
        return ships.back();
    }
    if (index < 0 || index >= ships_count) {
        return nullptr;
    }

    return ships[index];
}
