#ifndef SHIP_HPP
#define SHIP_HPP

class Ship; // Forward declaration

struct Segment {
    int hp;
    Ship *belongsTo;
};

class Ship {
   public:
    enum Orientation { HORIZONTAL, VERTICAL };

    Ship();
    Ship(int len, int index);
    ~Ship();
    int takeDamage(int segmentIndex, int damage);
    Segment *getSegment(int index);
    int getHealth();
    int getShipIndex();
    int getLenght();
    bool isAlive();

   private:
    int len;
    int health;
    bool is_alive;
    int ship_index;
    Segment *segments;
};

#endif  // SHIP_HPP