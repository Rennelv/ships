#ifndef GUI_HPP
#define GUI_HPP

#include <SFML/Graphics.hpp>
#include <memory>

#include "Game.hpp"
#include "GuiStates/State.hpp"

class GameGui {
   public:
    GameGui(const Game& game);
    void run();
    void mainLoop();
    void render();
   private:
    const Game &game;
    void update();
    void pollEvents();

    sf::RenderWindow window;
    sf::Event event;

    std::unique_ptr<RendererState> state;

    void changeState();

};

#endif  // GUI_HPP