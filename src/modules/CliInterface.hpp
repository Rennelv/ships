#ifndef CLIINTERFACE_HPP
#define CLIINTERFACE_HPP

#include "ShipField.hpp"
#include "ShipManager.hpp"

class CliInterface {
   public:
    void printField(const ShipField &field) const;
    void printFieldExposed(const ShipField &field, bool show_hp = false) const;
    void createField(ShipField *&field);
    void createShips(ShipManager *&manager);
    void placeShips(ShipField *&field, ShipManager *&manager);
    void attackShip(ShipField *&field);
    void printAliveShips(ShipManager *&manager) const;

};



#endif  // CLIINTERFACE_HPP