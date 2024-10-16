#ifndef ATTACKINGSHIPSTATE_HPP
#define ATTACKINGSHIPSTATE_HPP

#include <SFML/Graphics.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Window/Event.hpp>

#include "Abilities/AbilityManager.hpp"
#include "GuiStates/State.hpp"
#include "ShipField.hpp"
#include "ShipManager.hpp"

class AttackingShipsState : public State {
    GameState nextState = GameState::AttackingShips;
    ShipField &field;
    ShipManager &shipManager;
    AbilityManager &abilityManager;
    sf::Font font;
    sf::Text instructionText;
    sf::Text resultText;
    sf::RectangleShape selectionBox;
    sf::Vector2f drawOffset;
    sf::Vector2f cellSize;
    int drawOffsetX;
    int drawOffsetY;
    int currentX;
    int currentY;
    int dealDamage;
    void drawField(sf::RenderWindow &window);

   public:
    AttackingShipsState(ShipField &field, ShipManager &shipManager, AbilityManager &abilityManager);
    void handleInput(sf::Event &event) override;
    void update() override;
    void render(sf::RenderWindow &window) override;
    GameState changeState() override;
};

#endif  // ATTACKINGSHIPSTATE_HPP