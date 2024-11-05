#ifndef PLACINGSHIPSTATE_HPP
#define PLACINGSHIPSTATE_HPP

#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Window/Event.hpp>

#include "Enums.hpp"
#include "GuiStates/State.hpp"
#include "Player.hpp"

class PlacingShipsState : public State {
    GameState nextState = GameState::PlacingShips;
    Player& player;
    size_t currentShipIndex;
    ShipOrientation orientation = ShipOrientation::VERTICAL;
    sf::Font font;
    sf::Text instructionText;
    sf::Text resultText;
    sf::RectangleShape shipRepresentation;
    sf::Vector2f drawOffset;
    sf::Vector2f cellSize;
    size_t currentX;
    size_t currentY;
    void drawField(sf::RenderWindow& window);
    void placeShipHelper();

   public:
    PlacingShipsState(Player& player);
    void handleInput(sf::Event& event) override;
    void update() override;
    void render(sf::RenderWindow& window) override;
    GameState changeState() override;
};

#endif  // PLACINGSHIPSTATE_HPP