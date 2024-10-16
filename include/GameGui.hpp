#ifndef GUI_HPP
#define GUI_HPP

#include <SFML/Graphics.hpp>
#include <memory>

#include "Abilities/AbilityManager.hpp"
#include "GuiStates/State.hpp"  // Include the base state class and derived state classes
#include "ShipField.hpp"
#include "ShipManager.hpp"

class GameGui {
   public:
    GameGui();
    ~GameGui() = default;
    void run();
    void mainLoop();
    // void drawField(ShipField& field, int x_offset, int y_offset, bool show_ships);

   private:
    std::unique_ptr<ShipField> shipField;
    std::unique_ptr<ShipManager> shipManager;
    std::unique_ptr<AbilityManager> abilityManager;
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