#ifndef GAME_HPP
#define GAME_HPP
#include "ShipField.hpp"
#include "ShipManager.hpp"

class Game {
    public:
        Game();
        ~Game();
        void run();
    private:
        void printField(const ShipField *field);
        void printFieldExposed(const ShipField *field, bool show_hp = false);
        ShipField *field;
        ShipManager *manager;
};

#endif  // GAME_HPP