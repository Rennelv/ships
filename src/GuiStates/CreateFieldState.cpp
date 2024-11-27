#include "GuiStates/CreateFieldState.hpp"

#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/Shape.hpp>

#include "AiPlayer.hpp"

CreateFieldState::CreateFieldState(Player &player, AiPlayer &player2) : player(player), player2(player2) {
    draw_offset = {10, 50};
    cell_size = {20, 20};

    field_width = player.getField().getWidth();
    field_height = player.getField().getHeight();

    font.loadFromFile("assets/fonts/font.ttf");
    field_size_text.setFont(font);
    field_size_text.setCharacterSize(24);
    field_size_text.setFillColor(sf::Color::White);
    field_size_text.setPosition(10, 10);
}

void CreateFieldState::handleInput(sf::Event &event) {
    if (event.type == sf::Event::KeyPressed) {
        switch (event.key.code) {
            case sf::Keyboard::Up:
                field_height = std::min(30, field_height + 1);
                break;
            case sf::Keyboard::Down:
                field_height = std::max(5, field_height - 1);
                break;
            case sf::Keyboard::Right:
                field_width = std::min(30, field_width + 1);
                break;
            case sf::Keyboard::Left:
                field_width = std::max(5, field_width - 1);
                break;
            case sf::Keyboard::Enter:
                player.createField(field_width, field_height);   // Create the field for the 1 player
                player2.createField(field_width, field_height);  // Create the field for the 2 player
                next_state = GameState::CreateShips;             // Change to the next state
                break;
            case sf::Keyboard::Escape:
                player.createField(10, 10);
                next_state = GameState::Menu;  // Go back to the menu
                break;
            default:
                break;
        }
    }
}

void CreateFieldState::update() {
    field_size_text.setString("Field Size: " + std::to_string(field_width) + " x " + std::to_string(field_height));
}

void CreateFieldState::render(sf::RenderWindow &window) {
    window.clear();
    window.draw(field_size_text);
    drawField(window);
    window.display();
}

GameState CreateFieldState::changeState() {
    return next_state;
}

void CreateFieldState::drawField(sf::RenderWindow &window) {
    sf::RectangleShape cell_shape;
    cell_shape.setSize(cell_size);  // Set the size of each cell
    cell_shape.setOutlineColor(sf::Color::Black);
    cell_shape.setOutlineThickness(1.f);
    cell_shape.setFillColor(sf::Color::Cyan);
    for (int y = 0; y < field_height; ++y) {
        for (int x = 0; x < field_width; ++x) {
            cell_shape.setPosition(draw_offset.x + x * cell_size.x, draw_offset.y + y * cell_size.y);
            window.draw(cell_shape);
        }
    }
}
