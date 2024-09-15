#include "Ship.hpp"

Ship::Segment::Segment() : hp(2), belongsTo(nullptr) {
}

Ship::Segment::Segment(Ship *belongsTo) : hp(2), belongsTo(belongsTo) {
}

Ship *Ship::Segment::getBelongsTo() {
    return belongsTo;
}

int Ship::Segment::getHp() {
    return hp;
}

int Ship::Segment::damage(int damage) {
    hp -= damage;
    if (hp <= 0) {
        belongsTo->health -= 1;
        if (belongsTo->health == 0) {
            belongsTo->is_alive = false;
        }
    }
    return hp;
}

Ship::Ship() : len(0), segments(nullptr), health(0), is_alive(true) {
}

Ship::Ship(int new_len) {
    len = new_len;
    health = len;
    is_alive = true;
    segments = new Segment[len];
    for (int i = 0; i < len; i++) {
        segments[i] = Segment(this);
    }
}

Ship::Segment *Ship::getSegment(int index) {
    return &segments[index];
}


int Ship::takeDamage(int segmentIndex, int damage) {
    segments[segmentIndex].damage(damage);
    if (segments[segmentIndex].getHp() <= 0) {
        health--;
    }
    if (health == 0) {
        is_alive = false;
    }
    return segments[segmentIndex].getHp();
}

int Ship::getHealth() {
    return health;
}

int Ship::getLenght() {
    return len;
}

bool Ship::isAlive() {
    return is_alive;
}

Ship::~Ship() {
    delete[] segments;
}