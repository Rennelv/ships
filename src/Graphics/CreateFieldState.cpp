#include "CreateFieldState.hpp"

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
            field = new ShipField(fieldWidth, fieldHeight);  // Swap the field with a new one
            nextState = GameState::PlacingShips;             // Change to the next state
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
    window.draw(fieldRepresentation);
    window.display();
}

GameState CreateFieldState::changeState() {
    return nextState;
}