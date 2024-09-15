#ifndef SHIPFIELD_HPP
#define SHIPFIELD_HPP

#include "Ship.hpp"
#include "ShipManager.hpp"

class ShipField {
   public:
    ShipField(int width, int height);
    ~ShipField();
    void setManager(ShipManager *manager);
    bool placeShip(Ship *ship, int x, int y, Ship::Orientation orientation);
    bool placeNewShip(int length, int x, int y, Ship::Orientation orientation);
    bool checkPlace(int x, int y);
    void printField();
    bool attackShip(int x, int y);
    std::pair<int, int> getSizes();

   private:
    int width;
    int height;
    Ship::Segment ***field;
    ShipManager *manager;
};

#endif  // SHIPFIELD_HPP