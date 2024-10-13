#ifndef PLACINGSHIPSTATE_HPP
#define PLACINGSHIPSTATE_HPP

#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Font.hpp>
#include <SFML/Window/Event.hpp>

#include "ShipField.hpp"
#include "ShipManager.hpp"
#include "state.hpp"

class PlacingShipsState : public State {
    GameState nextState = GameState::PlacingShips;
    ShipField& field;
    ShipManager& manager;
    int currentShipIndex;
    bool isVertical;
    sf::Font font;
    sf::Text instructionText;
    sf::RectangleShape shipRepresentation;
    int currentX = 0;
    int currentY = 0;

   public:
    PlacingShipsState(ShipField& field, ShipManager& manager);
    void handleInput(sf::Event& event) override;
    void update() override;
    void render(sf::RenderWindow& window) override;
    GameState changeState() override;
};

#endif  // PLACINGSHIPSTATE_HPP