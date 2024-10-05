#ifndef SHIPMANAGER_HPP
#define SHIPMANAGER_HPP

#include <vector>

#include "Ship.hpp"

class ShipManager {
    std::vector<Ship*> ships;
    int ships_count;

   public:
    ShipManager();
    ShipManager(int count, int* lengths);
    ~ShipManager();
    int getShipCount();
    int getAliveCount();
    Ship* getShip(int index);
};

#endif  // SHIPMANAGER_HPP