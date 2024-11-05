#include "ShipManager.hpp"

#include <stdexcept>

#include "Ship.hpp"

ShipManager::ShipManager() {
    ships_count = 0;
}

ShipManager::ShipManager(size_t count, size_t* lengths) {
    ships.reserve(count);
    ships_count = count;
    for (size_t i = 0; i < ships_count; i++) {
        ships.emplace_back(lengths[i]);
    }
}

size_t ShipManager::getShipCount() const {
    return ships_count;
}

size_t ShipManager::getAliveCount() const {
    size_t alive = 0;
    for (size_t i = 0; i < ships_count; i++) {
        if (ships[i].isAlive()) {
            alive++;
        }
    }
    return alive;
}

size_t ShipManager::getShipLength(size_t index) const {
    if (index >= ships_count) {
        throw std::out_of_range("Index out of range");
    }

    return ships.at(index).getLength();
}

Ship& ShipManager::getShip(size_t index) {
    if (index >= ships_count) {
        throw std::out_of_range("Index out of range");
    }

    return ships.at(index);
}