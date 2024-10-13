#include "AttackingShipsState.hpp"

#include <SFML/Graphics.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Window/Event.hpp>

#include "Enums.hpp"
#include "ShipField.hpp"
#include "ShipManager.hpp"

AttackingShipsState::AttackingShipsState(ShipField &field, ShipManager &manager) : field(field), manager(manager), currentX(0), currentY(0) {
    font.loadFromFile("assets/fonts/font.ttf");
    instructionText.setFont(font);
    instructionText.setCharacterSize(24);
    instructionText.setFillColor(sf::Color::White);
    instructionText.setPosition(10, 10);
    instructionText.setString("Use arrow keys to move, Enter to attack");

    resultText.setFont(font);
    resultText.setCharacterSize(24);
    resultText.setFillColor(sf::Color::Red);
    resultText.setPosition(10, 40);

    selectionBox.setSize(sf::Vector2f(20, 20));
    selectionBox.setFillColor(sf::Color::Transparent);
    selectionBox.setOutlineColor(sf::Color::Yellow);
    selectionBox.setOutlineThickness(2);
}

void AttackingShipsState::handleInput(sf::Event &event) {
    if (event.type == sf::Event::KeyPressed) {
        if (event.key.code == sf::Keyboard::Up) {
            if (currentY > 0) currentY--;
        } else if (event.key.code == sf::Keyboard::Down) {
            if (currentY < field.getHeight() - 1) currentY++;
        } else if (event.key.code == sf::Keyboard::Left) {
            if (currentX > 0) currentX--;
        } else if (event.key.code == sf::Keyboard::Right) {
            if (currentX < field.getWidth() - 1) currentX++;
        } else if (event.key.code == sf::Keyboard::Enter) {
            try {
                field.attackShip(currentX, currentY);
                // resultText.setString(hit ? "Hit!" : "Miss!");
            } catch (const std::exception &e) {
                resultText.setString(e.what());
            }
        }
    }
}

void AttackingShipsState::update() {
    selectionBox.setPosition(10 + currentX * 20, 50 + currentY * 20);
}

void AttackingShipsState::render(sf::RenderWindow &window) {
    window.clear();
    window.draw(instructionText);
    window.draw(resultText);

    // Draw the field
    drawField(window);

    // Draw the selection box
    window.draw(selectionBox);

    window.display();

    if (manager.getAliveCount() == 0) {
        nextState = GameState::Exit;
    }
}

GameState AttackingShipsState::changeState() {
    return nextState;
}

void AttackingShipsState::drawField(sf::RenderWindow &window) {
    sf::RectangleShape cellShape;
    cellShape.setSize(sf::Vector2f(20.f, 20.f));  // Set the size of each cell
    cellShape.setOutlineColor(sf::Color::Black);
    cellShape.setOutlineThickness(1.f);
    for (int y = 0; y < field.getHeight(); ++y) {
        for (int x = 0; x < field.getWidth(); ++x) {
            CellVisibilityState cellState = field.getCellVisibilityState(x, y);
            switch (cellState) {
                case CellVisibilityState::UNKNOWN:
                    cellShape.setFillColor(sf::Color::Cyan);
                    break;
                case CellVisibilityState::BLANK:
                    cellShape.setFillColor(sf::Color::White);
                    break;
                case CellVisibilityState::SHIP:
                    switch (field.getShipSegmentState(x, y)) {
                        case ShipSegmentState::INTACT:
                            cellShape.setFillColor(sf::Color::Blue);
                            break;
                        case ShipSegmentState::DAMAGED:
                            cellShape.setFillColor(sf::Color::Yellow);
                            break;
                        case ShipSegmentState::DESTROYED:
                            cellShape.setFillColor(sf::Color::Red);
                            break;
                    }
                    break;
                default:
                    cellShape.setFillColor(sf::Color::Black);
                    break;
            }
            cellShape.setPosition(10 + x * cellShape.getSize().x, 50 + y * cellShape.getSize().y);
            window.draw(cellShape);
        }
    }
}