#include "GuiStates/CreateFieldState.hpp"

#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/Shape.hpp>

#include "AiPlayer.hpp"

CreateFieldState::CreateFieldState(Player &player, AiPlayer &aiPlayer) : player(player), aiPlayer(aiPlayer) {
    drawOffset = {10, 50};
    cellSize = {20, 20};

    font.loadFromFile("assets/fonts/font.ttf");
    fieldSizeText.setFont(font);
    fieldSizeText.setCharacterSize(24);
    fieldSizeText.setFillColor(sf::Color::White);
    fieldSizeText.setPosition(10, 10);
}

void CreateFieldState::handleInput(sf::Event &event) {
    if (event.type == sf::Event::KeyPressed) {
        if (event.key.code == sf::Keyboard::Up) {
            fieldHeight = std::min(20, fieldHeight + 1);
        } else if (event.key.code == sf::Keyboard::Down) {
            fieldHeight = std::max(1, fieldHeight - 1);
        } else if (event.key.code == sf::Keyboard::Right) {
            fieldWidth = std::min(20, fieldWidth + 1);
        } else if (event.key.code == sf::Keyboard::Left) {
            fieldWidth = std::max(1, fieldWidth - 1);
        } else if (event.key.code == sf::Keyboard::Enter) {
            player.createField(fieldWidth, fieldHeight);
            aiPlayer.createField(fieldWidth, fieldHeight);
            nextState = GameState::CreateShips;  // Change to the next state
        }
    }
}

void CreateFieldState::update() {
    fieldSizeText.setString("Field Size: " + std::to_string(fieldWidth) + " x " + std::to_string(fieldHeight));
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
    cellShape.setSize(cellSize);  // Set the size of each cell
    cellShape.setOutlineColor(sf::Color::Black);
    cellShape.setOutlineThickness(1.f);
    cellShape.setFillColor(sf::Color::Cyan);
    for (int y = 0; y < fieldHeight; ++y) {
        for (int x = 0; x < fieldWidth; ++x) {
            cellShape.setPosition(drawOffset.x + x * cellSize.x, drawOffset.y + y * cellSize.y);
            window.draw(cellShape);
        }
    }
}
