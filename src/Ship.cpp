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

// Copy constructor
Ship::Ship(const Ship& other) : length(other.length), health(other.health), segments(new Segment[other.length]) {
    for (size_t i = 0; i < length; ++i) {
        segments[i] = other.segments[i];
    }
}

// Copy assignment operator
Ship& Ship::operator=(const Ship& other) {
    if (this != &other) {
        delete[] segments;  // Free existing memory

        length = other.length;
        health = other.health;
        segments = new Segment[length];
        for (size_t i = 0; i < length; ++i) {
            segments[i] = other.segments[i];
        }
    }
    return *this;
}

// Move constructor
Ship::Ship(Ship&& other) noexcept : length(other.length), health(other.health), segments(other.segments) {
    other.segments = nullptr;
    other.length = 0;
    other.health = 0;
}

// Move assignment operator
Ship& Ship::operator=(Ship&& other) noexcept {
    if (this != &other) {
        delete[] segments;  // Free existing memory

        length = other.length;
        health = other.health;
        segments = other.segments;

        other.segments = nullptr;
        other.length = 0;
        other.health = 0;
    }
    return *this;
}

std::ostream& operator<<(std::ostream& os, const Ship& ship) {
    os << "===Ship===\n";
    os << ship.length << ' ';
    os << ship.health << ' ';
    for (size_t i = 0; i < ship.length; i++) {
        os << ship.segments[i].hp << ' ' << static_cast<int>(ship.segments[i].state) << '\n';
    }
    os << "===End Ship===\n";
    return os;
}

std::istream& operator>>(std::istream& is, Ship& ship) {
    is >> std::ws;
    std::string line;
    std::getline(is, line);
    if (line != "===Ship===") {
        throw std::invalid_argument("Invalid save file");
    }
    int len, health;
    is >> len;
    is >> health;
    ship = Ship(len);
    ship.health = health;
    for (size_t i = 0; i < ship.length; ++i) {
        int hp;
        int state;
        is >> hp >> state;
        ship.segments[i].hp = hp;
        ship.segments[i].state = static_cast<ShipSegmentState>(state);
    }

    is >> std::ws;
    std::getline(is, line);
    if (line != "===End Ship===") {
        throw std::invalid_argument("Invalid save file");
    }
    return is;
}

bool Ship::operator==(const Ship& other) const {
    if (length != other.length || health != other.health) {
        return false;
    }
    for (size_t i = 0; i < length; i++) {
        if (segments[i].hp != other.segments[i].hp || segments[i].state != other.segments[i].state) {
            return false;
        }
    }
    return true;
}

bool Ship::operator!=(const Ship& other) const {
    return !(*this == other);
}