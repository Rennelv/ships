#ifndef GUI_HPP
#define GUI_HPP

#include <SFML/Graphics.hpp>
#include <memory>

#include "ShipField.hpp"
#include "ShipManager.hpp"
#include "state.hpp"  // Include the base state class and derived state classes

class GameGui {
   public:
    GameGui();
    ~GameGui();
    void run();
    void mainLoop();
    void drawField(ShipField& field, int x_offset, int y_offset, bool show_ships);

   private:
    ShipField* shipField;
    ShipManager* shipManager;
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