#include "Ship.hpp"

#include <stdexcept>

#include "Enums.hpp"

Ship::Ship(int len) {
    if (len <= 0) {
        throw std::invalid_argument("Invalid length passed in ship constructor. Length must be greater than 0");
    }
    length = static_cast<size_t>(len);
    health = static_cast<size_t>(len);
    segments = new Segment[length];
    for (size_t i = 0; i < length; i++) {
        segments[i] = Segment{};
    }
}

Ship::~Ship() {
    delete[] segments;
}

int Ship::getSegmentHP(size_t index) const {
    if (index >= length) {
        throw std::out_of_range("Index out of range");
    }

    return segments[index].hp;
}

ShipSegmentState Ship::getSegmentState(size_t index) const {
    if (index >= length) {
        throw std::out_of_range("Index out of range");
    }

    return segments[index].state;
}

void Ship::takeDamage(size_t segment_index, int damage) {
    if (segment_index >= length) {
        throw std::out_of_range("Index out of range");
    }

    if (segments[segment_index].state == ShipSegmentState::DESTROYED) {
        return;
    }
    segments[segment_index].hp -= damage;
    if (segments[segment_index].hp <= 0) {
        health--;
        segments[segment_index].state = ShipSegmentState::DESTROYED;
    } else {
        segments[segment_index].state = ShipSegmentState::DAMAGED;
    }
}

size_t Ship::getLength() const {
    return length;
}

bool Ship::isAlive() const {
    return health > 0;
}