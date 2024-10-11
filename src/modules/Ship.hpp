#ifndef SHIP_HPP
#define SHIP_HPP

#include <cstddef>

#include "Enums.hpp"

class Ship {
    struct Segment {
        ShipSegmentState state = ShipSegmentState::INTACT;
        int hp = 2;
    };

    size_t length;
    size_t health;
    Segment* segments;

   public:
    Ship(int length);
    ~Ship();

    void takeDamage(size_t segment_index, int damage);     // deals damage to segment by index
    int getSegmentHP(size_t index) const;                  // returns hp of segment by index
    ShipSegmentState getSegmentState(size_t index) const;  // returns state of segment by index
    size_t getLength() const;                              // returns length of ship
    bool isAlive() const;                                  // returns true if ship is alive
};

#endif  // SHIP_HPP