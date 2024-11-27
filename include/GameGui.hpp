#ifndef GUI_HPP
#define GUI_HPP

#include <SFML/Graphics.hpp>
#include <memory>

#include "AiPlayer.hpp"
#include "GuiStates/GameStates.hpp"
#include "GuiStates/State.hpp"
#include "Player.hpp"

class GameGui {
   public:
    GameGui();
    void run();
    void mainLoop();
    GameState getCurrentState() const;
    GameState getPrevState() const;

   private:
    Player player;
    Player player2;
    AiPlayer ai_controller;
    void update();
    void render();
    void pollEvents();

    sf::RenderWindow window;
    sf::Event event;

    GameState current_state;
    GameState prev_state;
    std::unique_ptr<State> state;

    void changeState(GameState new_state);

    friend std::ostream& operator<<(std::ostream& os, const GameGui& state);

    friend std::istream& operator>>(std::istream& is, GameGui& state);
};

#endif  // GUI_HPP