#ifndef ATTACKINGSHIPSTATE_HPP
#define ATTACKINGSHIPSTATE_HPP

#include <SFML/Graphics.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Window/Event.hpp>

#include "GuiStates/State.hpp"
#include "Player.hpp"

class AttackingShipsState : public State {
    GameState nextState = GameState::AttackingShips;

    Player &player;

    sf::Font font;
    sf::Text instructionText;
    sf::Text resultText;
    sf::RectangleShape selectionBox;
    sf::Vector2f drawOffset;
    sf::Vector2f cellSize;
    size_t currentX;
    size_t currentY;

    void drawField(sf::RenderWindow &window);
    void onAbilityUse();
    void onAttackUse();

   public:
    AttackingShipsState(Player &player);
    void handleInput(sf::Event &event) override;
    void update() override;
    void render(sf::RenderWindow &window) override;
    GameState changeState() override;
};

#endif  // ATTACKINGSHIPSTATE_HPP