#include "GuiStates/AttackingShipsState.hpp"

#include <SFML/Graphics.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Window/Event.hpp>

#include "Enums.hpp"
#include "Exceptions/Exceptions.hpp"
#include "Player.hpp"

AttackingShipsState::AttackingShipsState(Player &player, AiPlayer &player2) : player(player), ai_player(player2) {
    current_x = 0;
    current_y = 0;
    draw_offset = {10, 70};
    draw_offset2 = {400, 70};
    cell_size = {20, 20};

    font.loadFromFile("assets/fonts/font.ttf");
    instruction_text.setFont(font);
    instruction_text.setCharacterSize(24);
    instruction_text.setFillColor(sf::Color::White);
    instruction_text.setPosition(10, 10);
    instruction_text.setString("Use arrow keys to move, Enter to attack, E to use ability");

    result_text.setFont(font);
    result_text.setCharacterSize(24);
    result_text.setFillColor(sf::Color::Red);
    result_text.setPosition(10, 40);

    selection_box.setSize(cell_size);
    selection_box.setFillColor(sf::Color::Transparent);
    selection_box.setOutlineColor(sf::Color::Yellow);
    selection_box.setOutlineThickness(2);
}

void AttackingShipsState::handleInput(sf::Event &event) {
    if (event.type == sf::Event::MouseButtonPressed) {
        if (event.mouseButton.button == sf::Mouse::Left) {
            onAttackUse();
        }
    }
    if (event.type == sf::Event::MouseMoved) {
        int x = (event.mouseMove.x - draw_offset2.x) / cell_size.x;
        int y = (event.mouseMove.y - draw_offset2.y) / cell_size.y;
        if (x >= 0 && x < static_cast<int>(player.getField().getWidth()) && y >= 0 && y < static_cast<int>(player.getField().getHeight())) {
            current_x = x;
            current_y = y;
        }
    }
    if (event.type == sf::Event::KeyPressed) {
        switch (event.key.code) {
            case sf::Keyboard::Up:
                if (current_y > 0) current_y--;
                break;
            case sf::Keyboard::Down:
                if (current_y < player.getField().getHeight() - 1) current_y++;
                break;
            case sf::Keyboard::Left:
                if (current_x > 0) current_x--;
                break;
            case sf::Keyboard::Right:
                if (current_x < player.getField().getWidth() - 1) current_x++;
                break;

            case sf::Keyboard::E:
                onAbilityUse();
                break;
            case sf::Keyboard::Enter:
                onAttackUse();
                break;
            case sf::Keyboard::Escape:
                next_state = GameState::SaveLoadState;
                break;
            default:
                break;
        }
    }
}

void AttackingShipsState::update() {
    selection_box.setPosition(draw_offset2.x + current_x * 20, draw_offset2.y + current_y * 20);
    if (player.scanner_is_active) {
        selection_box.setSize(cell_size * 2.f);
        selection_box.setOutlineColor(sf::Color::Green);
    } else {
        selection_box.setSize(cell_size);
        selection_box.setOutlineColor(sf::Color::Yellow);
    }

    if (ai_player.getPlayer().getAliveCount() == 0) {
        ai_player.reset();
    }

    if (player.getAliveCount() == 0) {
        // end the game
        next_state = GameState::Menu;
    }
}

void AttackingShipsState::render(sf::RenderWindow &window) {
    window.clear();
    window.draw(instruction_text);
    window.draw(result_text);

    // Draw the field
    drawField(window, player, draw_offset, true);

    drawField(window, ai_player.getPlayer(), draw_offset2);

    // Draw the selection box
    window.draw(selection_box);

    window.display();
}

GameState AttackingShipsState::changeState() {
    return next_state;
}

void AttackingShipsState::drawField(sf::RenderWindow &window, Player &player, sf::Vector2f draw_offset, bool god_eye) {
    sf::RectangleShape cell_shape;
    cell_shape.setSize(cell_size);  // Set the size of each cell
    cell_shape.setOutlineColor(sf::Color::Black);
    cell_shape.setOutlineThickness(1.f);
    for (size_t y = 0; y < player.getField().getHeight(); ++y) {
        for (size_t x = 0; x < player.getField().getWidth(); ++x) {
            CellVisibilityState cellState = player.getField().getCellVisibilityState(x, y);
            switch (cellState) {
                case CellVisibilityState::UNKNOWN:
                    if (player.getField().getIsShip(x, y) && god_eye) {
                        cell_shape.setFillColor(sf::Color::Blue);
                    } else {
                        cell_shape.setFillColor(sf::Color::Cyan);
                    }
                    break;
                case CellVisibilityState::BLANK:
                    cell_shape.setFillColor(sf::Color::White);
                    break;
                case CellVisibilityState::SHIP:
                    switch (player.getField().getShipSegmentState(x, y)) {
                        case ShipSegmentState::INTACT:
                            cell_shape.setFillColor(sf::Color::Blue);
                            break;
                        case ShipSegmentState::DAMAGED:
                            cell_shape.setFillColor(sf::Color::Yellow);
                            break;
                        case ShipSegmentState::DESTROYED:
                            cell_shape.setFillColor(sf::Color::Red);
                            break;
                    }
                    break;
                default:
                    cell_shape.setFillColor(sf::Color::Black);
                    break;
            }
            cell_shape.setPosition(draw_offset.x + x * cell_shape.getSize().x, draw_offset.y + y * cell_shape.getSize().y);
            window.draw(cell_shape);
        }
    }
}

void AttackingShipsState::onAbilityUse() {
    try {
        switch (player.getPendingAbilityType()) {
            case AbilityType::DoubleDamage:
                player.useAbility(ai_player.getPlayer(), current_x, current_y);
                result_text.setString("Double damage activated");
                break;
            case AbilityType::Scanner:
                if (player.scanner_is_active) {
                    player.scanner_is_active = false;
                    result_text.setString("Scanner deactivated. Ability not used");
                } else {
                    player.scanner_is_active = true;
                    result_text.setString("Scanner activated. Press Attack to scan");
                }
                break;
            case AbilityType::Bombard:
                player.useAbility(ai_player.getPlayer(), current_x, current_y);
                result_text.setString("Bombard activated");
                break;
        }
    } catch (const exceptions::NoAbilityAvailableException &e) {
        result_text.setString("No abilities available");
    } catch (const std::exception &e) {
        result_text.setString(e.what());
    }
};

void AttackingShipsState::onAttackUse() {
    // If the scanner is active use it
    if (player.scanner_is_active) {
        player.useAbility(ai_player.getPlayer(), current_x, current_y);
        if (player.getAbilityResults().ScannerShipFound)
            result_text.setString("Scanner used. Ship in range");
        else
            result_text.setString("Scanner used. No ship in range");
        player.scanner_is_active = false;
        return;
    }

    result_text.setString("");
    // else attack the cell
    try {
        player.attack(ai_player.getPlayer(), current_x, current_y, 1, true);
    } catch (const exceptions::OutOfBoundsAttackException &e) {
        result_text.setString("Coordinates are out of field bounds");
    } catch (const std::exception &e) {
        result_text.setString(e.what());
    }

    // Second player attacks
    ai_player.attack(player);
};