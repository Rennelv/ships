#ifndef GUI_HPP
#define GUI_HPP

#include <SFML/Graphics.hpp>
#include <memory>

#include "GuiStates/State.hpp"
#include "Player.hpp"

class GameGui {
   public:
    GameGui();
    void run();
    void mainLoop();

   private:
    Player player;
    void update();
    void render();
    void pollEvents();

    sf::RenderWindow window;
    sf::Event event;

    GameState current_state;
    std::unique_ptr<State> state;

    void changeState(GameState new_state);
};

#endif  // GUI_HPP