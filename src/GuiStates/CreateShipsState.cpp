#include "GuiStates/CreateShipsState.hpp"

#include <SFML/Graphics.hpp>
#include <vector>

#include "Player.hpp"

CreateShipState::CreateShipState(Player& player) : player(player), activeBoxIndex(0) {
    drawOffset = {10, 100};
    font.loadFromFile("assets/fonts/font.ttf");

    numberShipsText.setFont(font);

    titleText.setFont(font);
    titleText.setString("Number of ships:");
    titleText.setCharacterSize(24);
    titleText.setFillColor(sf::Color::White);
    titleText.setPosition(10, 10);

    shipsText.setFont(font);
    shipsText.setCharacterSize(24);
    shipsText.setFillColor(sf::Color::White);

    for (int i = 0; i < 4; ++i) {
        inputBoxes[i].box.setSize({100, 30});
        inputBoxes[i].box.setPosition(drawOffset.x, drawOffset.y + i * 100);
        inputBoxes[i].value = 4 - i;
    }
}

void CreateShipState::update() {
    // Update logic if needed
}

void CreateShipState::handleInput(sf::Event& event) {
    if (event.type == sf::Event::KeyPressed) {
        switch (event.key.code) {
            case sf::Keyboard::Up:
                activeBoxIndex = (activeBoxIndex - 1 + 4) % 4;
                break;
            case sf::Keyboard::Down:
                activeBoxIndex = (activeBoxIndex + 1) % 4;
                break;
            case sf::Keyboard::Add:
            case sf::Keyboard::Equal:  // For '+' key
                if (inputBoxes[activeBoxIndex].value < 10) inputBoxes[activeBoxIndex].value++;
                break;
            case sf::Keyboard::Subtract:
            case sf::Keyboard::Hyphen:  // For '-' key
                if (inputBoxes[activeBoxIndex].value > 0) inputBoxes[activeBoxIndex].value--;
                break;
            case sf::Keyboard::Enter: {
                createShips();
                nextState = GameState::PlacingShips;
            } break;
            default:
                break;
        }
    }
}

void CreateShipState::createShips() {
    std::vector<size_t> lengths;
    lengths.reserve(10);
    for (int i = 3; i >= 0; --i) {
        for (int j = 0; j < inputBoxes[i].value; ++j) {
            lengths.push_back(i + 1);
        }
    }
    player.createShipManager(lengths.size(), lengths.data());
}

void CreateShipState::render(sf::RenderWindow& window) {
    window.clear();
    window.draw(titleText);
    for (int i = 0; i < 4; ++i) {
        inputBoxes[i].box.setFillColor(sf::Color::White);
        inputBoxes[activeBoxIndex].box.setFillColor(sf::Color::Green);
        window.draw(inputBoxes[i].box);

        shipsText.setString("Ship of length " + std::to_string(i + 1) + ":");
        shipsText.setPosition(inputBoxes[i].box.getPosition() + sf::Vector2f(0, -30));
        window.draw(shipsText);

        numberShipsText.setString(std::to_string(inputBoxes[i].value));
        numberShipsText.setPosition(inputBoxes[i].box.getPosition());
        numberShipsText.setCharacterSize(24);
        numberShipsText.setFillColor(sf::Color::Black);
        window.draw(numberShipsText);
    }
    window.display();
}

GameState CreateShipState::changeState() {
    return nextState;
}
