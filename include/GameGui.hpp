#ifndef GUI_HPP
#define GUI_HPP

#include <SFML/Graphics.hpp>
#include <memory>

#include "AiPlayer.hpp"
#include "GuiStates/State.hpp"  // Include the base state class and derived state classes
#include "Player.hpp"

class GameGui {
   public:
    GameGui();
    ~GameGui() = default;
    void run();
    void mainLoop();

   private:
    Player player;
    AiPlayer aiPlayer;
    void update();
    void render();
    void pollEvents();

    sf::RenderWindow window;
    sf::Event event;

    GameState currentState;
    std::unique_ptr<State> state;

    void changeState(GameState newState);
};

#endif  // GUI_HPP