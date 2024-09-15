#include "ShipManager.hpp"

#include "Ship.hpp"

ShipManager::ShipManager() : count(0) {
}

ShipManager::ShipManager(int count, int* lengths) {
    ships.reserve(count);
    this->count = count;
    for (int i = 0; i < count; i++) {
        ships.push_back(newShip(lengths[i]));
    }
}

ShipManager::~ShipManager() {
    for (int i = 0; i < count; i++) {
        delete ships[i];
    }
}

Ship* ShipManager::newShip(int len) {
    return new Ship(len);
}

Ship* ShipManager::addNewShip(int len) {
    Ship* new_ship = newShip(len);
    ships.push_back(new_ship);
    count++;
    return ships[count - 1];
}

void ShipManager::addShip(Ship* ship) {
    ships.push_back(ship);
    count++;
}

int ShipManager::getCount() {
    return count;
}

Ship* ShipManager::getShip(int index) {
    return ships[index];
}
