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
    void createField(Player& player, int width, int height);
    void createShips(Player& player, size_t count, size_t* lengths);
    void createShips(AiPlayer& player, size_t count, size_t* lengths);
    void placeShip(Player& player, size_t index, int x, int y, ShipOrientation orientation);
    void placeShips(AiPlayer& player);
    // game actions
    void attack(Player& player, Player& target_player, int x, int y);
    void attack(AiPlayer& player, Player& target_player);
    void useAbility(Player& player, Player& target_player, int x, int y);
    void saveGame();
    void loadGame();
    // ???
    void resetPlayer(Player& player);
    void resetGame();
    // getters
    Player& getPlayer();
    AiPlayer& getAiController();
};

#endif  // GAME_HPP