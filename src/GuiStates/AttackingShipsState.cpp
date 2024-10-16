#include "GuiStates/AttackingShipsState.hpp"

#include <SFML/Graphics.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Window/Event.hpp>

#include "Abilities/AbilityManager.hpp"
#include "Enums.hpp"
#include "ShipField.hpp"
#include "ShipManager.hpp"

AttackingShipsState::AttackingShipsState(ShipField &field, ShipManager &shipManager, AbilityManager &abilityManager)
    : field(field), shipManager(shipManager), abilityManager(abilityManager) {
    currentX = 0;
    currentY = 0;
    drawOffset = {10, 70};
    cellSize = {20, 20};
    dealDamage = 1;
    font.loadFromFile("assets/fonts/font.ttf");
    instructionText.setFont(font);
    instructionText.setCharacterSize(24);
    instructionText.setFillColor(sf::Color::White);
    instructionText.setPosition(10, 10);
    instructionText.setString("Use arrow keys to move, Enter to attack, E to use ability");

    resultText.setFont(font);
    resultText.setCharacterSize(24);
    resultText.setFillColor(sf::Color::Red);
    resultText.setPosition(10, 40);

    selectionBox.setSize(cellSize);
    selectionBox.setFillColor(sf::Color::Transparent);
    selectionBox.setOutlineColor(sf::Color::Yellow);
    selectionBox.setOutlineThickness(2);
}

void AttackingShipsState::handleInput(sf::Event &event) {
    if (event.type == sf::Event::KeyPressed) {
        switch (event.key.code) {
            case sf::Keyboard::Up:
                if (currentY > 0) currentY--;
                break;
            case sf::Keyboard::Down:
                if (currentY < field.getHeight() - 1) currentY++;
                break;
            case sf::Keyboard::Left:
                if (currentX > 0) currentX--;
                break;
            case sf::Keyboard::Right:
                if (currentX < field.getWidth() - 1) currentX++;
                break;

            case sf::Keyboard::E:
                try {
                    if (abilityManager.getAbilityType() == AbilityType::DoubleDamage) {
                        abilityManager.useAbility(field, currentX, currentY);
                        resultText.setString("Double damage activated");
                    } else if (abilityManager.getAbilityType() == AbilityType::Scanner) {
                        abilityManager.useAbility(field, currentX, currentY);
                        resultText.setString("Scanner activated. Press Enter to scan");
                    } else if (abilityManager.getAbilityType() == AbilityType::Bombard) {
                        abilityManager.useAbility(field, currentX, currentY);
                        resultText.setString("Bombard activated");
                    }

                } catch (const std::exception &e) {
                    resultText.setString(e.what());
                }
                break;
            case sf::Keyboard::Enter:
                if (abilityManager.getAbilityStatus().scannerIsActive) {
                    abilityManager.useAbility(field, currentX, currentY);
                    if (abilityManager.getAbilityStatus().scannerShipFound)
                        resultText.setString("Scanner used. Ship in range");
                    else
                        resultText.setString("Scanner used. No ship in range");

                    break;
                }
                try {
                    field.attackShip(currentX, currentY, true, dealDamage);
                    abilityManager.getAbilityStatus().doubleDamageIsActive = false;

                } catch (const std::exception &e) {
                    resultText.setString(e.what());
                }
                break;
            default:
                break;
        }
    }
}

void AttackingShipsState::update() {
    selectionBox.setPosition(drawOffset.x + currentX * 20, drawOffset.y + currentY * 20);
    if (abilityManager.getAbilityStatus().scannerIsActive) {
        selectionBox.setSize(cellSize * 2.f);
        selectionBox.setOutlineColor(sf::Color::Green);
    } else {
        selectionBox.setSize(cellSize);
        selectionBox.setOutlineColor(sf::Color::Yellow);
    }
    dealDamage = abilityManager.getAbilityStatus().doubleDamageIsActive ? 2 : 1;
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

    if (shipManager.getAliveCount() == 0) {
        nextState = GameState::Exit;
    }
}

GameState AttackingShipsState::changeState() {
    return nextState;
}

void AttackingShipsState::drawField(sf::RenderWindow &window) {
    sf::RectangleShape cellShape;
    cellShape.setSize(cellSize);  // Set the size of each cell
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
            cellShape.setPosition(drawOffset.x + x * cellShape.getSize().x, drawOffset.y + y * cellShape.getSize().y);
            window.draw(cellShape);
        }
    }
}