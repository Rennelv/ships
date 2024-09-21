#include "Ship.hpp"

Ship::Ship(int new_len, int index) {
    len = new_len;
    health = len;
    is_alive = true;
    ship_index = index;
    segments = new Segment[len];
    for (int i = 0; i < len; i++) {
        segments[i] = Segment{2, this};
    }
}

Ship::~Ship() {
    delete[] segments;
}

Segment *Ship::getSegment(int index) {
    return &segments[index];
}

int Ship::takeDamage(int segmentIndex, int damage) {
    segments[segmentIndex].hp -= damage;
    if (segments[segmentIndex].hp <= 0) {
        health--;
    }
    if (health == 0) {
        is_alive = false;
    }
    return segments[segmentIndex].hp;
}

int Ship::getHealth() {
    return health;
}

int Ship::getLenght() {
    return len;
}

int Ship::getShipIndex() {
    return ship_index;
}

bool Ship::isAlive() {
    return is_alive;
}