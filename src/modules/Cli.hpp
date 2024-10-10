#ifndef CLI_HPP
#define CLI_HPP

#include "ShipField.hpp"
#include "ShipManager.hpp"

class Cli {
   public:
    void printField(const ShipField &field) const;
    void printFieldExposed(const ShipField &field, bool show_hp = false) const;
    void createField(ShipField *&field);
    void createShips(ShipManager *&manager);
    void placeShips(ShipField *&field, ShipManager *&manager);
    void attackShip(ShipField *&field);
    void printAliveShips(ShipManager *&manager) const;

};



#endif  // CLI_HPP