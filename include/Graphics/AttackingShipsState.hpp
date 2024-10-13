#ifndef ATTACKINGSHIPSTATE_HPP
#define ATTACKINGSHIPSTATE_HPP

#include <SFML/Graphics.hpp>
#include <SFML/Window/Event.hpp>

#include "ShipField.hpp"
#include "ShipManager.hpp"
#include "state.hpp"

class AttackingShipsState : public State {
    GameState nextState = GameState::AttackingShips;
    ShipField &field;
    ShipManager &manager;
    sf::Font font;
    sf::Text instructionText;
    sf::Text resultText;
    sf::RectangleShape selectionBox;
    int currentX;
    int currentY;

   public:
    AttackingShipsState(ShipField &field, ShipManager &manager);
    void handleInput(sf::Event &event) override;
    void update() override;
    void render(sf::RenderWindow &window) override;
    GameState changeState() override;
};

#endif  // ATTACKINGSHIPSTATE_HPP