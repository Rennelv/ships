#include "Ship.hpp"

Ship::Ship(int len, int index) {
    length = len;
    health = len;
    is_alive = true;
    ship_index = index;
    segments = new Segment[length];
    for (int i = 0; i < len; i++) {
        segments[i] = Segment{2};
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
    for (int i = 0; i < length; i++) {
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
        for (int i = 0; i < length; i++) {
            segments[i] = other.segments[i];
        }
    }
    return *this;
}


Segment Ship::getSegment(int index) {
    return segments[index];
}

int Ship::takeDamage(int segment_index, int damage) {
    segments[segment_index].hp -= damage;
    if (segments[segment_index].hp <= 0) {
        health--;
    }
    if (health == 0) {
        is_alive = false;
    }
    return segments[segment_index].hp;
}

int Ship::getHealth() {
    return health;
}

int Ship::getLenght() {
    return length;
}

int Ship::getShipIndex() {
    return ship_index;
}

bool Ship::isAlive() {
    return is_alive;
}