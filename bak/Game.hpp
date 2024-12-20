#ifndef GAME_HPP
#define GAME_HPP
#include "ShipField.hpp"
#include "ShipManager.hpp"

class Game {
    ShipField *field;
    ShipManager *manager;

   public:
    Game();
    ~Game();
    void runCli();
    void runGui();
    void run();
};

#endif  // GAME_HPP