#include "ShipManager.hpp"

#include <iostream>
#include <istream>
#include <ostream>
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

const Ship& ShipManager::getShip(size_t index) const {
    if (index >= ships_count) {
        throw std::out_of_range("Index out of range");
    }

    return ships.at(index);
}

std::ostream& operator<<(std::ostream& os, const ShipManager& manager) {
    os << "===ShipManager===\n";
    os << manager.ships_count << '\n';
    for (size_t i = 0; i < manager.ships_count; i++) {
        os << manager.ships[i].getLength() << ' ';
    }
    os << '\n';
    for (size_t i = 0; i < manager.ships_count; i++) {
        os << i << '\n';
        os << manager.ships[i];
    }
    os << "===End ShipManager===\n";
    return os;
}

std::istream& operator>>(std::istream& is, ShipManager& manager) {
    std::string line;
    is >> std::ws;
    std::getline(is, line);
    if (line != "===ShipManager===") {
        throw std::invalid_argument("Invalid save file");
    }
    int size;
    is >> size;
    std::vector<size_t> lengths(size);
    for (size_t i = 0; i < lengths.size(); i++) {
        is >> lengths[i];
    }
    manager = ShipManager(lengths.size(), lengths.data());
    for (size_t i = 0; i < manager.getShipCount(); i++) {
        is >> i;
        is >> manager.ships[i];
    }
    is >> std::ws;
    std::getline(is, line);
    if (line != "===End ShipManager===") {
        throw std::invalid_argument("Invalid save file");
    }
    return is;
}

bool ShipManager::operator==(const ShipManager& other) const {
    if (ships_count != other.ships_count) {
        return false;
    }
    for (size_t i = 0; i < ships_count; i++) {
        if (ships[i] != other.ships[i]) {
            return false;
        }
    }
    return true;
}

bool ShipManager::operator!=(const ShipManager& other) const {
    return !(*this == other);
}