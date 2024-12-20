#ifndef GUI_HPP
#define GUI_HPP

#include <SFML/Graphics.hpp>
#include <memory>

#include "Enums.hpp"
#include "Game.hpp"
#include "GuiStates/State.hpp"

class Gui {
   public:
    Gui(const Game& game);
    // void run();
    // void mainLoop();
    void render();
    void printErr(std::string msg);
   private:
    const Game &game;
    Stage prevStage;
    // void update();
    // void pollEvents();

    sf::RenderWindow window;
    // sf::Event event;

    std::unique_ptr<RendererState> state;

    void changeState();

};

#endif  // GUI_HPP