#ifndef GUI_HPP
#define GUI_HPP

#include <SFML/Graphics.hpp>
#include <memory>
#include <vector>

#include "GuiStates/State.hpp"
#include "Player.hpp"

class GameGui {
   public:
    GameGui();
    ~GameGui() = default;
    void run();
    void mainLoop();

   private:
    std::vector<State> states;
    Player player;
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