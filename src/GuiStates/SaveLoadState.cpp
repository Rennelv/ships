#include "GuiStates/SaveLoadState.hpp"

#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Window/Event.hpp>
#include <fstream>

#include "GameGui.hpp"

SaveLoadState::SaveLoadState(GameGui& game_gui) : game(game_gui) {
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
            next_state = game.getPrevState();
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

GameState SaveLoadState::changeState() {
    return next_state;
}

void SaveLoadState::loadGameHelper() {
    std::ifstream file("save.txt");
    if (!file.is_open()) {
        result_text.setString("Failed to load game");
        return;
    }

    try {
        file >> game;
    } catch (const std::exception& e) {
        result_text.setString("Failed to load game");
    }

    file.close();
}

void SaveLoadState::saveGameHelper() {
    std::ofstream file("save.txt");
    if (!file.is_open()) {
        result_text.setString("Failed to save game");
        return;
    }

    try {
        file << game;
        result_text.setString("Game saved successfully");
    } catch (const std::exception& e) {
        result_text.setString("Failed to save game");
    }

    file.close();
}