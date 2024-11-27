#ifndef GAME_HPP
#define GAME_HPP

#include "AiPlayer.hpp"
#include "Player.hpp"

class Game {
    Player player;
    Player player2;
    AiPlayer ai_controller;

   public:
    Game();
    // init game
    void createField(Player& player);
    void createShips(Player& player);
    void placeShips(Player& player);
    // game actions
    void attack(Player& player, Player& target_player, int x, int y);
    void useAbility(Player& player, Player& target_player, int x, int y);
    void saveGame();
    void loadGame();

    void resetPlayer(Player& player);
    void resetGame();
};

#endif  // GAME_HPP