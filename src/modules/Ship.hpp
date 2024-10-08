#ifndef SHIP_HPP
#define SHIP_HPP

#include <cstddef>

class Ship {
   public:
    enum SegmentState { INTACT = 2, DAMAGED = 1, DESTROYED = 0 };
    enum Orientation { HORIZONTAL, VERTICAL };

   private:
    struct Segment {
        SegmentState state = SegmentState::INTACT;
        int hp = 2;
    };

    size_t length;
    int health;
    Segment* segments;

   public:
    Ship(size_t len);
    ~Ship();

    int takeDamage(size_t segment_index, int damage);  // returns current hp of segment
    int getSegmentHP(size_t index) const;              // returns hp of segment by index
    SegmentState getSegmentState(size_t index) const;  // returns state of segment by index
    size_t getLenght() const;                          // returns length of ship
    bool isAlive() const;                              // returns true if ship is alive
};

#endif  // SHIP_HPP