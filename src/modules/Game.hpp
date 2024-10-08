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
        ShipField *field;
        ShipManager *manager;
};

#endif  // GAME_HPP