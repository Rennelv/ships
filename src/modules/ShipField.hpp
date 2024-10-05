#ifndef SHIPFIELD_HPP
#define SHIPFIELD_HPP

#include "Ship.hpp"

struct FieldElement {
    enum VisibilityState { UNKNOWN, BLANK, SHIP };
    VisibilityState state;
    int x, y;
    Ship* ship;
    bool is_ship;
    int ship_index;
    int segment_index;
};

class ShipField {
    int width;
    int height;
    FieldElement** field;

   public:
    ShipField(int width, int height);
    ~ShipField();

    ShipField(const ShipField& other);                 // Copy constructor
    ShipField(ShipField&& other) noexcept;             // Move constructor
    ShipField& operator=(const ShipField& other);      // Copy assignment operator
    ShipField& operator=(ShipField&& other) noexcept;  // Move assignment operator

    int getWidth();
    int getHeight();
    FieldElement getCell(int x, int y);
    bool placeShip(Ship* ship, int x, int y, Ship::Orientation orientation);
    bool checkPlace(int x, int y);
    bool attackShip(int x, int y);
};

#endif  // SHIPFIELD_HPP