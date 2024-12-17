#ifndef GAMESTATE_HPP
#define GAMESTATE_HPP

#include "AiPlayer.hpp"
#include "Player.hpp"

class GameState {
    Player player;
    Player player2;
    AiPlayer ai_controller;
    Stage current_stage;

   public:
    GameState();
    Player& getPlayer();
    Player& getPlayer2();
    AiPlayer& getAiController();
    Stage& getCurrentStage();

    void saveGame();
    void loadGame();

    friend std::ostream& operator<<(std::ostream& os, const GameState& game_state);
    friend std::istream& operator>>(std::istream& is, GameState& game_state);
};

#endif  // GAMESTATE_HPP