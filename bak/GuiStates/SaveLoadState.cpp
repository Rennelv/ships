#include "GuiStates/SaveLoadState.hpp"

#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Window/Event.hpp>

SaveLoadState::SaveLoadState(Game& game) : game(game) {
    font.loadFromFile("assets/fonts/font.ttf");

    instruction_text.setFont(font);
    instruction_text.setCharacterSize(24);
    instruction_text.setFillColor(sf::Color::White);
    instruction_text.setPosition(10, 10);
    instruction_text.setString("Press Enter to load game\n Press Backspace to save game\n Press Escape to resume game");

    result_text.setFont(font);
    result_text.setCharacterSize(24);
    result_text.setFillColor(sf::Color::Red);
    result_text.setPosition(10, 200);
}

void SaveLoadState::handleInput(sf::Event& event) {
    if (event.type == sf::Event::KeyPressed) {
        if (event.key.code == sf::Keyboard::Enter) {
            loadGameHelper();
        }
        if (event.key.code == sf::Keyboard::BackSpace) {
            saveGameHelper();
        }
        if (event.key.code == sf::Keyboard::Escape) {
            // next_state = game.getPrevState();
        }
    }
}

void SaveLoadState::update() {
    //
}

void SaveLoadState::render(sf::RenderWindow& window) {
    window.clear();
    window.draw(instruction_text);
    window.draw(result_text);
    window.display();
}

GuiStates SaveLoadState::changeState() {
    return next_state;
}

void SaveLoadState::loadGameHelper() {
    try {
        game.loadGame();
        result_text.setString("Game loaded");
    } catch (const std::exception& e) {
        result_text.setString(e.what());
    }
}

void SaveLoadState::saveGameHelper() {
    try {
        game.saveGame();
        result_text.setString("Game saved");
    } catch (const std::exception& e) {
        result_text.setString(e.what());
    }
}