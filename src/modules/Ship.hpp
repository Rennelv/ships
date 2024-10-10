#ifndef SHIP_HPP
#define SHIP_HPP

#include "Enums.hpp"

#include <cstddef>

class Ship {
    struct Segment {
        ShipSegmentState state = ShipSegmentState::INTACT;
        int hp = 2;
    };

    size_t length;
    int health;
    Segment* segments;

   public:
    Ship(size_t len);
    ~Ship();

    void takeDamage(size_t segment_index, int damage);  // returns current hp of segment
    int getSegmentHP(size_t index) const;               // returns hp of segment by index
    ShipSegmentState getSegmentState(size_t index) const;   // returns state of segment by index
    size_t getLenght() const;                           // returns length of ship
    bool isAlive() const;                               // returns true if ship is alive
};

#endif  // SHIP_HPP