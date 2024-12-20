#include "GuiStates/CreateShipsState.hpp"

#include <SFML/Graphics.hpp>

CreateShipState::CreateShipState(const Game& game) : game(game), active_box_index(0) {
    draw_offset = {10, 100};
    font.loadFromFile("assets/fonts/font.ttf");

    number_ships_text.setFont(font);

    title_text.setFont(font);
    title_text.setString("CREATING SHIPS");
    title_text.setCharacterSize(24);
    title_text.setFillColor(sf::Color::White);
    title_text.setPosition(10, 10);

    ships_text.setFont(font);
    ships_text.setCharacterSize(24);
    ships_text.setFillColor(sf::Color::White);

    for (int i = 0; i < 4; ++i) {
        input_boxes[i].box.setSize({100, 30});
        input_boxes[i].box.setPosition(draw_offset.x, draw_offset.y + i * 100);
        input_boxes[i].value = 4 - i;
    }
}

void CreateShipState::update() {
    // Update logic if needed
}

// void CreateShipState::handleInput(sf::Event& event) {
//     if (event.type == sf::Event::KeyPressed) {
//         switch (event.key.code) {
//             case sf::Keyboard::Up:
//                 active_box_indт ex = (active_box_index - 1 + 4) % 4;
//                 break;
//             case sf::Keyboard::Down:
//                 active_box_index = (active_box_index + 1) % 4;
//                 break;
//             case sf::Keyboard::Add:
//             case sf::Keyboard::Equal:  // For '+' key
//                 if (input_boxes[active_box_index].value < 10) input_boxes[active_box_index].value++;
//                 break;
//             case sf::Keyboard::Subtract:
//             case sf::Keyboard::Hyphen:  // For '-' key
//                 if (input_boxes[active_box_index].value > 0) input_boxes[active_box_index].value--;
//                 break;
//             case sf::Keyboard::Enter: {
//                 createShips();
//             } break;
//             case sf::Keyboard::Escape:
//                 player.createShipManager(0, nullptr);
//                 break;
//             default:
//                 break;
//         }
//     }
// }

// void CreateShipState::createShips() {
//     std::vector<size_t> lengths;
//     lengths.reserve(10);
//     for (int i = 3; i >= 0; --i) {
//         for (int j = 0; j < input_boxes[i].value; ++j) {
//             lengths.push_back(i + 1);
//         }
//     }
//     player.createShipManager(lengths.size(), lengths.data());

//     player2.createShipManager(lengths.size(), lengths.data());
// }

void CreateShipState::render(sf::RenderWindow& window) {
    window.clear();
    if (!err) {
        title_text.setFillColor(sf::Color::White);
        title_text.setString("CREATING SHIPS");
    } else {
        err = false;
    }
    window.draw(title_text);
    // for (int i = 0; i < 4; ++i) {
    //     input_boxes[i].box.setFillColor(sf::Color::White);
    //     input_boxes[active_box_index].box.setFillColor(sf::Color::Green);
    //     window.draw(input_boxes[i].box);

    //     ships_text.setString("Ship of length " + std::to_string(i + 1) + ":");
    //     ships_text.setPosition(input_boxes[i].box.getPosition() + sf::Vector2f(0, -30));
    //     window.draw(ships_text);

    //     number_ships_text.setString(std::to_string(input_boxes[i].value));
    //     number_ships_text.setPosition(input_boxes[i].box.getPosition());
    //     number_ships_text.setCharacterSize(24);
    //     number_ships_text.setFillColor(sf::Color::Black);
    //     window.draw(number_ships_text);
    // }
    window.display();
}

void CreateShipState::printErr(std::string msg) {
    title_text.setString(msg);
    title_text.setFillColor(sf::Color::Red);
    err = true;
}