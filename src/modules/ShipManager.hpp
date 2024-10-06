#ifndef SHIPMANAGER_HPP
#define SHIPMANAGER_HPP

#include <vector>

#include "Ship.hpp"

class ShipManager {
    std::vector<Ship*> ships;
    size_t ships_count;

   public:
    ShipManager();
    ShipManager(size_t count, size_t* lengths);
    ~ShipManager();
    size_t getShipCount();
    size_t getAliveCount();
    Ship* getShip(int index);
};

#endif  // SHIPMANAGER_HPP