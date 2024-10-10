#include "Ship.hpp"

#include "Enums.hpp"

Ship::Ship(size_t length) : length(length), health(length) {
    segments = new Segment[length];
    for (size_t i = 0; i < length; i++) {
        segments[i] = Segment{};
    }
}

Ship::~Ship() {
    delete[] segments;
}

int Ship::getSegmentHP(size_t index) const {
    return segments[index].hp;
}

ShipSegmentState Ship::getSegmentState(size_t index) const {
    return segments[index].state;
}

void Ship::takeDamage(size_t segment_index, int damage) {
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