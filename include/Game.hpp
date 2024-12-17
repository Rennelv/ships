#ifndef GAME_HPP
#define GAME_HPP

#include "Abilities/AbilityType.hpp"
#include "AiPlayer.hpp"
#include "Enums.hpp"
#include "GameState.hpp"
#include "Player.hpp"

class Game {
    GameState game_state;

    Player& player;
    Player& player2;
    AiPlayer& ai_controller;
    Stage& current_stage;

    int current_ship_index;

   public:
    Game();
    void exit();
    // init game
    void createField(int width, int height);
    void createShips(size_t count, size_t* lengths);
    void placeShipByIndex(size_t index, int x, int y, ShipOrientation orientation);
    void placeShip(int x, int y, ShipOrientation orientation);
    void initAiPlayer();

    void nextStage();

    // game actions
    void attack(int x, int y);
    void useAbility(int x, int y);
    void saveGame();
    void loadGame();

    // ???
    void resetGame();
    void checkWin();

    // getters
    const Player& getPlayer() const;
    const Player& getPlayer2() const;
    const AiPlayer& getAiController() const;
    AbilityType getPendingAbilityType() const;
    Stage getCurrentStage() const;

};

#endif  // GAME_HPP