#ifndef SHIPMANAGER_HPP
#define SHIPMANAGER_HPP

#include <vector>

#include "Ship.hpp"

class ShipManager {
    std::vector<Ship> ships;
    size_t ships_count;

   public:
    ShipManager(size_t count, size_t* lengths);
    ~ShipManager() = default;
    size_t getShipCount() const;
    size_t getAliveCount() const;
    Ship& getShip(int index);
};

#endif  // SHIPMANAGER_HPP