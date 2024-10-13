#include "CreateFieldState.hpp"

#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/Shape.hpp>

#include "ShipField.hpp"

CreateFieldState::CreateFieldState(ShipField *&field) : field(field) {
    font.loadFromFile("assets/fonts/font.ttf");
    fieldSizeText.setFont(font);
    fieldSizeText.setCharacterSize(24);
    fieldSizeText.setFillColor(sf::Color::White);
    fieldSizeText.setPosition(10, 10);

    fieldRepresentation.setFillColor(sf::Color::Green);
    fieldRepresentation.setOutlineColor(sf::Color::White);
    fieldRepresentation.setOutlineThickness(1);
    fieldRepresentation.setPosition(10, 50);
}

void CreateFieldState::handleInput(sf::Event &event) {
    if (event.type == sf::Event::KeyPressed) {
        if (event.key.code == sf::Keyboard::Up) {
            fieldHeight++;
        } else if (event.key.code == sf::Keyboard::Down) {
            fieldHeight = std::max(1, fieldHeight - 1);
        } else if (event.key.code == sf::Keyboard::Right) {
            fieldWidth++;
        } else if (event.key.code == sf::Keyboard::Left) {
            fieldWidth = std::max(1, fieldWidth - 1);
        } else if (event.key.code == sf::Keyboard::Enter) {
            field = new ShipField(fieldWidth, fieldHeight);
            nextState = GameState::PlacingShips;  // Change to the next state
        }
    }
}

void CreateFieldState::update() {
    fieldSizeText.setString("Field Size: " + std::to_string(fieldWidth) + " x " + std::to_string(fieldHeight));
    fieldRepresentation.setSize(sf::Vector2f(fieldWidth * 20, fieldHeight * 20));  // Adjust size for visual representation
}

void CreateFieldState::render(sf::RenderWindow &window) {
    window.clear();
    window.draw(fieldSizeText);
    drawField(window);
    window.display();
}

GameState CreateFieldState::changeState() {
    return nextState;
}

void CreateFieldState::drawField(sf::RenderWindow &window) {
    sf::RectangleShape cellShape;
    cellShape.setSize(sf::Vector2f(30.f, 30.f));  // Set the size of each cell
    cellShape.setOutlineColor(sf::Color::Black);
    cellShape.setOutlineThickness(1.f);
    for (int y = 0; y < fieldHeight; ++y) {
        for (int x = 0; x < fieldWidth; ++x) {
            cellShape.setFillColor(sf::Color::Cyan);

            cellShape.setPosition(10 + x * 30.f, 50 + y * 30.f);
            window.draw(cellShape);
        }
    }
}
