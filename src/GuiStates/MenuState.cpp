#include "GuiStates/MenuState.hpp"

#include <SFML/Window/Event.hpp>

MenuState::MenuState() : selectedItemIndex(0) {
    font.loadFromFile("assets/fonts/font.ttf");

    std::vector<std::string> items = {"Start Game", "um", "Exit"};
    for (const auto &item : items) {
        sf::Text text;
        text.setFont(font);
        text.setString(item);
        text.setCharacterSize(24);
        text.setFillColor(sf::Color::White);
        menuItems.push_back(text);
    }

    // Position menu items
    for (size_t i = 0; i < menuItems.size(); ++i) {
        menuItems[i].setPosition(100, 100 + i * 30);
    }

    // Highlight the first item
    menuItems[selectedItemIndex].setFillColor(sf::Color::Red);
}

void MenuState::handleInput(sf::Event &event) {
    if (event.type == sf::Event::KeyPressed) {
        if (event.key.code == sf::Keyboard::Up) {
            moveUp();
        } else if (event.key.code == sf::Keyboard::Down) {
            moveDown();
        } else if (event.key.code == sf::Keyboard::Enter) {
            selectItem();
        }
    }
}

void MenuState::update() {
    // Update menu logic if needed
}

void MenuState::render(sf::RenderWindow &window) {
    window.clear();
    for (const auto &item : menuItems) {
        window.draw(item);
    }
    window.display();
}

void MenuState::moveUp() {
    if (selectedItemIndex > 0) {
        menuItems[selectedItemIndex].setFillColor(sf::Color::White);
        selectedItemIndex--;
        menuItems[selectedItemIndex].setFillColor(sf::Color::Red);
    }
}

void MenuState::moveDown() {
    if (selectedItemIndex < menuItems.size() - 1) {
        menuItems[selectedItemIndex].setFillColor(sf::Color::White);
        selectedItemIndex++;
        menuItems[selectedItemIndex].setFillColor(sf::Color::Red);
    }
}

GameState MenuState::changeState() {
    return nextState;
}

void MenuState::selectItem() {
    switch (selectedItemIndex) {
        case 0:
            nextState = GameState::CreateField;
            break;
        case 1:
            // Handle Options

            break;
        case 2:
            nextState = GameState::Exit;
            break;
    }
}
