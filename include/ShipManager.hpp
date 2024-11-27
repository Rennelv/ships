#ifndef SHIPMANAGER_HPP
#define SHIPMANAGER_HPP

#include <istream>
#include <ostream>
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
    const Ship& getShip(size_t index) const;

    friend std::ostream& operator<<(std::ostream& os, const ShipManager& manager);
    friend std::istream& operator>>(std::istream& is, ShipManager& manager);

    bool operator==(const ShipManager& other) const;
    bool operator!=(const ShipManager& other) const;
};

#endif  // SHIPMANAGER_HPP