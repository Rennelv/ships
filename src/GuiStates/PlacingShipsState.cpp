#include "GuiStates/PlacingShipsState.hpp"

#include <SFML/Graphics.hpp>
#include <SFML/Window/Event.hpp>

#include "AiPlayer.hpp"
#include "Enums.hpp"
#include "Player.hpp"

PlacingShipsState::PlacingShipsState(Player& player, AiPlayer& aiPlayer)
    : player(player), aiPlayer(aiPlayer), currentShipIndex(0), orientation(ShipOrientation::VERTICAL) {
    drawOffset = {10, 70};
    cellSize = {20, 20};

    font.loadFromFile("assets/fonts/font.ttf");
    instructionText.setFont(font);
    instructionText.setCharacterSize(24);
    instructionText.setFillColor(sf::Color::White);
    instructionText.setPosition(10, 10);
    instructionText.setString("Use arrow keys to move, R to rotate, Enter to place ship");

    resultText.setFont(font);
    resultText.setCharacterSize(24);
    resultText.setFillColor(sf::Color::Red);
    resultText.setPosition(10, 40);

    shipRepresentation.setFillColor(sf::Color::Blue);
    shipRepresentation.setOutlineColor(sf::Color::White);
    shipRepresentation.setOutlineThickness(1);
}

void PlacingShipsState::handleInput(sf::Event& event) {
    if (event.type == sf::Event::MouseButtonPressed) {
        if (event.mouseButton.button == sf::Mouse::Left) {
            placeShipHelper();
        }
    }
    if (event.type == sf::Event::MouseMoved) {
        int x = (event.mouseMove.x - drawOffset.x) / cellSize.x;
        int y = (event.mouseMove.y - drawOffset.y) / cellSize.y;
        if (x >= 0 && x < static_cast<int>(player.getField().getWidth()) && y >= 0 && y < static_cast<int>(player.getField().getHeight())) {
            currentX = x;
            currentY = y;
        }
    }
    if (event.type == sf::Event::KeyPressed) {
        if (event.key.code == sf::Keyboard::Up) {
            if (currentY > 0) currentY--;
        } else if (event.key.code == sf::Keyboard::Down) {
            if (currentY < player.getField().getHeight() - 1) currentY++;
        } else if (event.key.code == sf::Keyboard::Left) {
            if (currentX > 0) currentX--;
        } else if (event.key.code == sf::Keyboard::Right) {
            if (currentX < player.getField().getWidth() - 1) currentX++;
        } else if (event.key.code == sf::Keyboard::R) {
            if (orientation == ShipOrientation::VERTICAL) {
                orientation = ShipOrientation::HORIZONTAL;
            } else {
                orientation = ShipOrientation::VERTICAL;
            }
        } else if (event.key.code == sf::Keyboard::Enter) {
            placeShipHelper();
        }
    }
}

void PlacingShipsState::update() {
    if (currentShipIndex < player.getShipCount()) {
        int shipLength = player.getShipLength(currentShipIndex);
        if (orientation == ShipOrientation::VERTICAL) {
            shipRepresentation.setSize(sf::Vector2f(cellSize.x, shipLength * cellSize.y));
        } else {
            shipRepresentation.setSize(sf::Vector2f(shipLength * cellSize.x, cellSize.y));
        }
        shipRepresentation.setPosition(drawOffset.x + currentX * cellSize.x, drawOffset.y + currentY * cellSize.y);
    }
}

void PlacingShipsState::render(sf::RenderWindow& window) {
    window.clear();
    window.draw(instructionText);
    window.draw(resultText);

    // Draw the field
    drawField(window);

    // Draw the current ship
    if (currentShipIndex < player.getShipCount()) {
        window.draw(shipRepresentation);
    }

    window.display();
}

GameState PlacingShipsState::changeState() {
    return nextState;
}

void PlacingShipsState::drawField(sf::RenderWindow& window) {
    sf::RectangleShape cellShape(cellSize);
    cellShape.setOutlineColor(sf::Color::White);
    cellShape.setOutlineThickness(1);
    for (size_t y = 0; y < player.getField().getHeight(); y++) {
        for (size_t x = 0; x < player.getField().getWidth(); x++) {
            cellShape.setPosition(drawOffset.x + x * cellSize.x, drawOffset.y + y * cellSize.y);
            cellShape.setFillColor(player.getField().getIsShip(x, y) ? sf::Color::Red : sf::Color::Green);
            window.draw(cellShape);
        }
    }
}

void PlacingShipsState::placeShipHelper() {
    try {
        player.placeShipByIndex(currentShipIndex, currentX, currentY, orientation);
    } catch (const std::exception& e) {
        currentShipIndex--;
        resultText.setString(e.what());
    }
    currentShipIndex++;
    if (currentShipIndex >= player.getShipCount()) {
        aiPlayer.placeShipsRandomly();
        nextState = GameState::AttackingShips;  // Change to the next state
    }
}