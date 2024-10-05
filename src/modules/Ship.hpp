#ifndef SHIP_HPP
#define SHIP_HPP

class Ship;

struct Segment {
    int hp;
};

class Ship {
    int length;
    int health;
    bool is_alive;
    int ship_index;
    Segment* segments;

   public:
    enum Orientation { HORIZONTAL, VERTICAL };

    Ship();
    Ship(int len, int index);
    Ship(const Ship& other);
    Ship& operator=(const Ship& other);
    Ship(Ship&& other) noexcept = delete;
    Ship& operator=(Ship&& other) = delete;
    ~Ship();

    int takeDamage(int segment_index, int damage);
    Segment getSegment(int index);
    int getHealth();
    int getShipIndex();
    int getLenght();
    bool isAlive();
};

#endif  // SHIP_HPP