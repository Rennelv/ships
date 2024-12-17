#include "GuiStates/MenuState.hpp"

#include <SFML/Window/Event.hpp>

MenuState::MenuState() : selected_item_index(0) {
    font.loadFromFile("assets/fonts/font.ttf");

    std::vector<std::string> items = {"Start Game", "Load Game", "Exit"};
    for (const auto &item : items) {
        sf::Text text;
        text.setFont(font);
        text.setString(item);
        text.setCharacterSize(24);
        text.setFillColor(sf::Color::White);
        menu_items.push_back(text);
    }

    // Position menu items
    for (size_t i = 0; i < menu_items.size(); ++i) {
        menu_items[i].setPosition(100, 100 + i * 30);
    }

    // Highlight the first item
    menu_items[selected_item_index].setFillColor(sf::Color::Red);
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
    //
}

void MenuState::render(sf::RenderWindow &window) {
    window.clear();
    for (const auto &item : menu_items) {
        window.draw(item);
    }
    window.display();
}

void MenuState::moveUp() {
    if (selected_item_index > 0) {
        menu_items[selected_item_index].setFillColor(sf::Color::White);
        selected_item_index--;
        menu_items[selected_item_index].setFillColor(sf::Color::Red);
    }
}

void MenuState::moveDown() {
    if (selected_item_index < menu_items.size() - 1) {
        menu_items[selected_item_index].setFillColor(sf::Color::White);
        selected_item_index++;
        menu_items[selected_item_index].setFillColor(sf::Color::Red);
    }
}

GuiStates MenuState::changeState() {
    return next_state;
}

void MenuState::selectItem() {
    switch (selected_item_index) {
        case 0:
            next_state = GuiStates::CreateField;
            break;
        case 1:
            // Handle Options
            next_state = GuiStates::SaveLoadState;
            break;
        case 2:
            next_state = GuiStates::Exit;
            break;
    }
}
