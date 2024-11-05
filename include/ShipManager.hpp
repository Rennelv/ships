#ifndef SHIPMANAGER_HPP
#define SHIPMANAGER_HPP

#include <vector>

#include "Ship.hpp"

class ShipManager {
    std::vector<Ship> ships;
    size_t ships_count;

   public:
    ShipManager();
    ShipManager(size_t count, size_t* lengths);
    ~ShipManager() = default;
    size_t getShipCount() const;
    size_t getAliveCount() const;
    size_t getShipLength(size_t index) const;
    Ship& getShip(size_t index);
};

#endif  // SHIPMANAGER_HPP