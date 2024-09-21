#ifndef SHIPFIELD_HPP
#define SHIPFIELD_HPP

#include "Ship.hpp"

struct FieldElement {
    enum VisibilityState { UNKNOWN, BLANK, SHIP };
    VisibilityState state;
    int x, y;
    Ship *ship;
    bool is_ship;
    int ship_index;
    int segment_index;
};

class ShipField {
   public:
    ShipField(int width, int height);
    ~ShipField();

    // Copy constructor
    ShipField(const ShipField& other); 

    // Move constructor
    ShipField(ShipField&& other) noexcept;

    // Copy assignment operator
    ShipField& operator=(const ShipField& other);

    // Move assignment operator
    ShipField& operator=(ShipField&& other) noexcept;

    bool placeShip(Ship *ship, int x, int y, Ship::Orientation orientation);
    bool checkPlace(int x, int y);
    void printField(bool expose_ships = false);
    bool attackShip(int x, int y);

   private:
    int width;
    int height;
    FieldElement **field;

    void copyField(const ShipField& other);
    void moveField(ShipField&& other);
    void clearField();
};

#endif  // SHIPFIELD_HPP