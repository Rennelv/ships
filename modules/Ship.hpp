#ifndef SHIP_HPP
#define SHIP_HPP

class Ship {
   public:
    enum Orientation { HORIZONTAL, VERTICAL };

    class Segment {
       public:
        Segment();
        Segment(Ship *belongsTo);
        int getHp();
        int damage(int damage);
        Ship *getBelongsTo();

       private:
        int hp;
        Ship *belongsTo;
    };

    Ship();
    Ship(int len);
    ~Ship();
    int takeDamage(int segmentIndex, int damage);
    Ship::Segment *getSegment(int index);
    int getHealth();
    int getLenght();
    bool isAlive();

   private:
    int len;
    int health;
    bool is_alive;
    Segment *segments;
};

#endif  // SHIP_HPP