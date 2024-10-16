#include "GuiStates/AttackingShipsState.hpp"

#include <SFML/Graphics.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Window/Event.hpp>

#include "Enums.hpp"
#include "Player.hpp"

AttackingShipsState::AttackingShipsState(Player &player) : player(player) {
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
    if (event.type == sf::Event::MouseButtonPressed) {
        if (event.mouseButton.button == sf::Mouse::Left) {
            attackShipHelper();
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
        switch (event.key.code) {
            case sf::Keyboard::Up:
                if (currentY > 0) currentY--;
                break;
            case sf::Keyboard::Down:
                if (currentY < player.getField().getHeight() - 1) currentY++;
                break;
            case sf::Keyboard::Left:
                if (currentX > 0) currentX--;
                break;
            case sf::Keyboard::Right:
                if (currentX < player.getField().getWidth() - 1) currentX++;
                break;

            case sf::Keyboard::E:
                useAbilityHelper();
                break;
            case sf::Keyboard::Enter:
                attackShipHelper();
                break;
            default:
                break;
        }
    }
}

void AttackingShipsState::update() {
    selectionBox.setPosition(drawOffset.x + currentX * 20, drawOffset.y + currentY * 20);
    if (player.getAbilityStatus().scannerIsActive) {
        selectionBox.setSize(cellSize * 2.f);
        selectionBox.setOutlineColor(sf::Color::Green);
    } else {
        selectionBox.setSize(cellSize);
        selectionBox.setOutlineColor(sf::Color::Yellow);
    }
    dealDamage = player.getAbilityStatus().doubleDamageIsActive ? 2 : 1;
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

    if (player.getShipManager().getAliveCount() == 0) {
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
    for (size_t y = 0; y < player.getField().getHeight(); ++y) {
        for (size_t x = 0; x < player.getField().getWidth(); ++x) {
            CellVisibilityState cellState = player.getField().getCellVisibilityState(x, y);
            switch (cellState) {
                case CellVisibilityState::UNKNOWN:
                    cellShape.setFillColor(sf::Color::Cyan);
                    break;
                case CellVisibilityState::BLANK:
                    cellShape.setFillColor(sf::Color::White);
                    break;
                case CellVisibilityState::SHIP:
                    switch (player.getField().getShipSegmentState(x, y)) {
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

void AttackingShipsState::useAbilityHelper() {
    try {
        if (player.getAbilityManager().getPendingAbilityType() == AbilityType::DoubleDamage) {
            player.useAbility(currentX, currentY);
            resultText.setString("Double damage activated");
        } else if (player.getAbilityManager().getPendingAbilityType() == AbilityType::Scanner) {
            if (player.getAbilityStatus().scannerIsActive) {
                player.getAbilityStatus().scannerIsActive = false;
                resultText.setString("Scanner deactivated. Ability not used");
                return;
            }
            player.useAbility(currentX, currentY);
            resultText.setString("Scanner activated. Press Enter to scan");
        } else if (player.getAbilityManager().getPendingAbilityType() == AbilityType::Bombard) {
            player.useAbility(currentX, currentY);
            resultText.setString("Bombard activated");
        }

    } catch (const std::exception &e) {
        resultText.setString(e.what());
    }
};

void AttackingShipsState::attackShipHelper() {
    if (player.getAbilityStatus().scannerIsActive) {
        player.useAbility(currentX, currentY);
        if (player.getAbilityStatus().scannerShipFound)
            resultText.setString("Scanner used. Ship in range");
        else
            resultText.setString("Scanner used. No ship in range");

        return;
    }
    try {
        player.attackShip(currentX, currentY, true, dealDamage);
        player.getAbilityStatus().doubleDamageIsActive = false;

    } catch (const std::exception &e) {
        resultText.setString(e.what());
    }
};