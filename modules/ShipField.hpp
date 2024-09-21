#ifndef SHIPFIELD_HPP
#define SHIPFIELD_HPP

// #include "ShipManager.hpp"
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
    // void setManager(ShipManager *manager);
    bool placeShip(Ship *ship, int x, int y, Ship::Orientation orientation);
    bool checkPlace(int x, int y);
    void printField(bool expose_ships = false);
    bool attackShip(int x, int y);

   private:
    int width;
    int height;
    FieldElement **field;
    // ShipManager *manager;
};

#endif  // SHIPFIELD_HPP