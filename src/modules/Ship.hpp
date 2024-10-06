#ifndef SHIP_HPP
#define SHIP_HPP

#include <cstddef>

class Ship {
   public:
    enum SegmentState { ALIVE = 2, DAMAGED = 1, DESTROYED = 0 };

   private:
    struct Segment {
        SegmentState state;
        int hp;
    };
    
    size_t length;
    int health;
    bool is_alive;
    size_t ship_index;
    Segment* segments;

   public:
    enum Orientation { HORIZONTAL, VERTICAL };

    Ship(size_t len, size_t index);
    Ship(const Ship& other);
    Ship& operator=(const Ship& other);
    Ship(Ship&& other) = delete;
    Ship& operator=(Ship&& other) = delete;
    ~Ship();

    int takeDamage(size_t segment_index, int damage);  // returns current hp of segment
    Segment getSegment(size_t index) const;            // returns segment by index
    int getHealth() const;                             // returns health of ship
    size_t getShipIndex() const;                       // returns index of ship
    size_t getLenght() const;                          // returns length of ship
    bool isAlive() const;                              // returns true if ship is alive
};

#endif  // SHIP_HPP