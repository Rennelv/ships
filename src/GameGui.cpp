#include "GameGui.hpp"

#include <memory>

#include "GuiStates/AttackingShipsState.hpp"
#include "GuiStates/CreateFieldState.hpp"
#include "GuiStates/CreateShipsState.hpp"
#include "GuiStates/MenuState.hpp"
#include "GuiStates/PlacingShipsState.hpp"

GameGui::GameGui() {
    window.create(sf::VideoMode(1600, 900), "Battlefield 0", sf::Style::Close | sf::Style::Titlebar);
    window.setFramerateLimit(60);
    // sf::ContextSettings settings;
    // settings.antialiasingLevel = 8;
    changeState(GameState::Menu);
}

void GameGui::changeState(GameState new_state) {
    switch (new_state) {
        case GameState::Menu:
            current_state = new_state;
            state = std::make_unique<MenuState>();
            break;
        case GameState::PlacingShips:
            current_state = new_state;
            state = std::make_unique<PlacingShipsState>(player);
            break;
        case GameState::AttackingShips:
            current_state = new_state;
            state = std::make_unique<AttackingShipsState>(player);
            break;
        case GameState::CreateField:
            current_state = new_state;
            state = std::make_unique<CreateFieldState>(player);
            break;
        case GameState::CreateShips:
            current_state = new_state;
            state = std::make_unique<CreateShipState>(player);
            break;
        case GameState::Exit:
            window.close();
    }
}

void GameGui::pollEvents() {
    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            changeState(GameState::Exit);
            break;
        }
        state->handleInput(event);
    }
}

void GameGui::update() {
    pollEvents();
    state->update();
}

void GameGui::render() {
    state->render(window);
}

void GameGui::mainLoop() {
    while (window.isOpen()) {
        update();
        render();
        if (state->changeState() != current_state) {
            changeState(state->changeState());
        }
    }
}

void GameGui::run() {
    mainLoop();
}
