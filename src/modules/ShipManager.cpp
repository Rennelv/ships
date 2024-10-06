#include "ShipManager.hpp"

#include "Ship.hpp"

ShipManager::ShipManager() : ships_count(0) {
}

ShipManager::ShipManager(size_t count, size_t* lengths) {
    ships.reserve(count);
    ships_count = count;
    for (size_t i = 0; i < ships_count; i++) {
        // Ship* newShip = new Ship(lengths[i], ships.size());
        // ships.push_back(newShip);
        ships.emplace_back(new Ship(lengths[i], ships.size()));
    }
}

ShipManager::~ShipManager() {
    for (size_t i = 0; i < ships_count; i++) {
        delete ships[i];
    }
    ships.clear();

}

size_t ShipManager::getShipCount() {
    return ships_count;
}

size_t ShipManager::getAliveCount() {
    size_t alive = 0;
    for (size_t i = 0; i < ships_count; i++) {
        if (ships[i]->isAlive()) {
            alive++;
        }
    }
    return alive;
}

Ship* ShipManager::getShip(int index) {
    if (index < 0) {
        index = ships_count - index;
    }
    if (static_cast<size_t>(index) >= ships_count) {
        return nullptr;
    }

    return ships[index];
}
