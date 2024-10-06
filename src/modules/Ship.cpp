#include "Ship.hpp"

Ship::Ship(size_t len, size_t index) {
    length = len;
    health = len;
    is_alive = true;
    ship_index = index;
    segments = new Segment[length];
    for (size_t i = 0; i < len; i++) {
        segments[i] = Segment{.state = SegmentState::ALIVE, .hp = 2};
    }
}

Ship::~Ship() {
    delete[] segments;
}

// Copy constructor
Ship::Ship(const Ship& other) {
    length = other.length;
    health = other.health;
    is_alive = other.is_alive;
    ship_index = other.ship_index;
    segments = new Segment[length];
    for (size_t i = 0; i < length; i++) {
        segments[i] = other.segments[i];
    }
}

// Copy assignment operator
Ship& Ship::operator=(const Ship& other) {
    if (this != &other) {
        length = other.length;
        health = other.health;
        is_alive = other.is_alive;
        ship_index = other.ship_index;
        delete[] segments;
        segments = new Segment[length];
        for (size_t i = 0; i < length; i++) {
            segments[i] = other.segments[i];
        }
    }
    return *this;
}

Ship::Segment Ship::getSegment(size_t index) const {
    return segments[index];
}

int Ship::takeDamage(size_t segment_index, int damage) {
    segments[segment_index].hp -= damage;
    if (segments[segment_index].hp <= 0) {
        health--;
        segments[segment_index].state = SegmentState::DESTROYED;
    } else {
        segments[segment_index].state = SegmentState::DAMAGED;
    }
    if (health == 0) {
        is_alive = false;
    }
    return segments[segment_index].hp;
}

int Ship::getHealth() const {
    return health;
}

size_t Ship::getLenght() const {
    return length;
}

size_t Ship::getShipIndex() const {
    return ship_index;
}

bool Ship::isAlive() const {
    return is_alive;
}