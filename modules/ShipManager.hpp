#ifndef SHIPMANAGER_HPP
#define SHIPMANAGER_HPP

#include <vector>

#include "Ship.hpp"

class ShipManager {
   public:
    ShipManager();
    ShipManager(int count, int* lengths);
    ~ShipManager();
    Ship* newShip(int len);
    void addShip(Ship* ship);
    Ship* addNewShip(int len);
    int getCount();
    Ship* getShip(int index);

   private:
    std::vector<Ship*> ships;
    int count;
};

#endif  // SHIPMANAGER_HPP