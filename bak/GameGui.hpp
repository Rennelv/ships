#ifndef GUI_HPP
#define GUI_HPP

#include <SFML/Graphics.hpp>
#include <memory>

#include "Game.hpp"
#include "GuiStates/GameStates.hpp"
#include "GuiStates/State.hpp"

class GameGui {
   public:
    GameGui(Game& game);
    void run();
    void mainLoop();
    GuiStates getCurrentState() const;
    GuiStates getPrevState() const;
    void aaaaaaaaa();

    void render();
   private:
    Game &game;
    void update();
    void pollEvents();

    sf::RenderWindow window;
    sf::Event event;

    GuiStates current_state;
    GuiStates prev_state;
    std::unique_ptr<RendererState> state;

    void changeState(GuiStates new_state);
    void changeState();

};

#endif  // GUI_HPP