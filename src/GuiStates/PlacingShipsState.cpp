#include "GuiStates/PlacingShipsState.hpp"

#include <SFML/Graphics.hpp>
#include <SFML/Window/Event.hpp>

#include "Enums.hpp"

PlacingShipsState::PlacingShipsState(ShipField& field, ShipManager& manager)
    : field(field), manager(manager), currentShipIndex(0), orientation(ShipOrientation::VERTICAL) {
    font.loadFromFile("assets/fonts/font.ttf");
    instructionText.setFont(font);
    instructionText.setCharacterSize(24);
    instructionText.setFillColor(sf::Color::White);
    instructionText.setPosition(10, 10);
    instructionText.setString("Use arrow keys to move, R to rotate, Enter to place ship");

    shipRepresentation.setFillColor(sf::Color::Blue);
    shipRepresentation.setOutlineColor(sf::Color::White);
    shipRepresentation.setOutlineThickness(1);
}

void PlacingShipsState::handleInput(sf::Event& event) {
    if (event.type == sf::Event::KeyPressed) {
        if (event.key.code == sf::Keyboard::Up) {
            if (currentY > 0) currentY--;
        } else if (event.key.code == sf::Keyboard::Down) {
            if (currentY < field.getHeight() - 1) currentY++;
        } else if (event.key.code == sf::Keyboard::Left) {
            if (currentX > 0) currentX--;
        } else if (event.key.code == sf::Keyboard::Right) {
            if (currentX < field.getWidth() - 1) currentX++;
        } else if (event.key.code == sf::Keyboard::R) {
            if (orientation == ShipOrientation::VERTICAL) {
                orientation = ShipOrientation::HORIZONTAL;
            } else {
                orientation = ShipOrientation::VERTICAL;
            }
        } else if (event.key.code == sf::Keyboard::Enter) {
            Ship& ship = manager.getShip(currentShipIndex);
            try {
                field.placeShip(ship, currentX, currentY, orientation);
            } catch (const std::exception& e) {
                currentShipIndex--;
            }
            currentShipIndex++;
            if (currentShipIndex >= manager.getShipCount()) {
                nextState = GameState::AttackingShips;  // Change to the next state
            }
        }
    }
}

void PlacingShipsState::update() {
    if (currentShipIndex < manager.getShipCount()) {
        int shipLength = manager.getShip(currentShipIndex).getLength();
        if (orientation == ShipOrientation::VERTICAL) {
            shipRepresentation.setSize(sf::Vector2f(20, shipLength * 20));
        } else {
            shipRepresentation.setSize(sf::Vector2f(shipLength * 20, 20));
        }
        shipRepresentation.setPosition(10 + currentX * 20, 50 + currentY * 20);
    }
}

void PlacingShipsState::render(sf::RenderWindow& window) {
    window.clear();
    window.draw(instructionText);

    // Draw the field
    drawField(window);

    // Draw the current ship
    if (currentShipIndex < manager.getShipCount()) {
        window.draw(shipRepresentation);
    }

    window.display();
}

GameState PlacingShipsState::changeState() {
    return nextState;
}

void PlacingShipsState::drawField(sf::RenderWindow& window) {
    sf::RectangleShape cellShape;
    cellShape.setSize(sf::Vector2f(30.f, 30.f));  // Set the size of each cell
    cellShape.setOutlineColor(sf::Color::Black);
    cellShape.setOutlineThickness(1.f);
    for (int y = 0; y < field.getHeight(); y++) {
        for (int x = 0; x < field.getWidth(); x++) {
            sf::RectangleShape cell(sf::Vector2f(20, 20));
            cell.setPosition(10 + x * 20, 50 + y * 20);
            cell.setFillColor(field.getIsShip(x, y) ? sf::Color::Red : sf::Color::Green);
            cell.setOutlineColor(sf::Color::White);
            cell.setOutlineThickness(1);
            window.draw(cell);
        }
    }
}
