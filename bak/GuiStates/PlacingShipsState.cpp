#include "GuiStates/PlacingShipsState.hpp"

#include <SFML/Graphics.hpp>
#include <SFML/Window/Event.hpp>

#include "Enums.hpp"
#include "Player.hpp"

PlacingShipsState::PlacingShipsState(Game& game) : current_ship_index(0), orientation(ShipOrientation::VERTICAL), game(game) {
    draw_offset = {10, 70};
    cell_size = {20, 20};

    current_x = 0;
    current_y = 0;

    font.loadFromFile("assets/fonts/font.ttf");
    instruction_text.setFont(font);
    instruction_text.setCharacterSize(24);
    instruction_text.setFillColor(sf::Color::White);
    instruction_text.setPosition(10, 10);
    instruction_text.setString("Use arrow keys to move, R to rotate, Enter to place ship");

    result_text.setFont(font);
    result_text.setCharacterSize(24);
    result_text.setFillColor(sf::Color::Red);
    result_text.setPosition(10, 40);

    ship_representation.setFillColor(sf::Color::Blue);
    ship_representation.setOutlineColor(sf::Color::White);
    ship_representation.setOutlineThickness(1);
}

void PlacingShipsState::handleInput(sf::Event& event) {
    if (event.type == sf::Event::MouseButtonPressed) {
        if (event.mouseButton.button == sf::Mouse::Left) {
            placeShipHelper();
        }
    }
    if (event.type == sf::Event::MouseMoved) {
        int x = (event.mouseMove.x - draw_offset.x) / cell_size.x;
        int y = (event.mouseMove.y - draw_offset.y) / cell_size.y;
        if (x >= 0 && x < static_cast<int>(game.getPlayer().getField().getWidth()) && y >= 0 && y < static_cast<int>(game.getPlayer().getField().getHeight())) {
            current_x = x;
            current_y = y;
        }
    }
    if (event.type == sf::Event::KeyPressed) {
        if (event.key.code == sf::Keyboard::Up) {
            if (current_y > 0) current_y--;
        } else if (event.key.code == sf::Keyboard::Down) {
            if (current_y < game.getPlayer().getField().getHeight() - 1) current_y++;
        } else if (event.key.code == sf::Keyboard::Left) {
            if (current_x > 0) current_x--;
        } else if (event.key.code == sf::Keyboard::Right) {
            if (current_x < game.getPlayer().getField().getWidth() - 1) current_x++;
        } else if (event.key.code == sf::Keyboard::R) {
            if (orientation == ShipOrientation::VERTICAL) {
                orientation = ShipOrientation::HORIZONTAL;
            } else {
                orientation = ShipOrientation::VERTICAL;
            }
        } else if (event.key.code == sf::Keyboard::Enter) {
            placeShipHelper();
        } else if (event.key.code == sf::Keyboard::Escape) {
            // player.createField(player.getField().getWidth(), player.getField().getHeight());
            game.createField(game.getPlayer().getField().getWidth(), game.getPlayer().getField().getHeight());
            next_state = GuiStates::CreateShips;
        }
    }
}

void PlacingShipsState::update() {
    if (current_ship_index < game.getPlayer().getShipCount()) {
        int shipLength = game.getPlayer().getShipLength(current_ship_index);
        if (orientation == ShipOrientation::VERTICAL) {
            ship_representation.setSize(sf::Vector2f(cell_size.x, shipLength * cell_size.y));
        } else {
            ship_representation.setSize(sf::Vector2f(shipLength * cell_size.x, cell_size.y));
        }
        ship_representation.setPosition(draw_offset.x + current_x * cell_size.x, draw_offset.y + current_y * cell_size.y);
    }
}

void PlacingShipsState::render(sf::RenderWindow& window) {
    window.clear();
    window.draw(instruction_text);
    window.draw(result_text);

    // Draw the field
    drawField(window);

    // Draw the current ship
    if (current_ship_index < game.getPlayer().getShipCount()) {
        window.draw(ship_representation);
    }

    window.display();
}

GuiStates PlacingShipsState::changeState() {
    return next_state;
}

void PlacingShipsState::drawField(sf::RenderWindow& window) {
    sf::RectangleShape cell_shape(cell_size);
    cell_shape.setOutlineColor(sf::Color::White);
    cell_shape.setOutlineThickness(1);
    for (size_t y = 0; y < game.getPlayer().getField().getHeight(); y++) {
        for (size_t x = 0; x < game.getPlayer().getField().getWidth(); x++) {
            cell_shape.setPosition(draw_offset.x + x * cell_size.x, draw_offset.y + y * cell_size.y);
            cell_shape.setFillColor(game.getPlayer().getField().getIsShip(x, y) ? sf::Color::Red : sf::Color::Green);
            window.draw(cell_shape);
        }
    }
}

void PlacingShipsState::placeShipHelper() {
    try {
        // player.placeShipByIndex(current_ship_index, current_x, current_y, orientation);
        game.placeShipByIndex(current_ship_index, current_x, current_y, orientation);
    } catch (const std::exception& e) {
        current_ship_index--;
        result_text.setString(e.what());
    }
    current_ship_index++;
    if (current_ship_index >= game.getPlayer().getShipCount()) {
        // player2.placeShipsRandom();              // Place ships for the AI player before changing the state
        game.initAiPlayer();                     // Place ships for the AI player before changing the state
        next_state = GuiStates::AttackingShips;  // Change to the next state
    }
}