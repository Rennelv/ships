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

void GameGui::changeState(GameState newState) {
    switch (newState) {
        case GameState::Menu:
            currentState = newState;
            state = std::make_unique<MenuState>();
            break;
        case GameState::PlacingShips:
            currentState = newState;
            state = std::make_unique<PlacingShipsState>(player, aiPlayer);
            break;
        case GameState::AttackingShips:
            currentState = newState;
            state = std::make_unique<AttackingShipsState>(player, aiPlayer);
            break;
        case GameState::CreateField:
            currentState = newState;
            state = std::make_unique<CreateFieldState>(player, aiPlayer);
            break;
        case GameState::CreateShips:
            currentState = newState;
            state = std::make_unique<CreateShipState>(player, aiPlayer);
            break;
        case GameState::Exit:
            window.close();
            // Add other states as needed
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
        if (state->changeState() != currentState) {
            changeState(state->changeState());
        }
    }
}

void GameGui::run() {
    mainLoop();
}
