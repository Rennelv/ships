#include "GameGui.hpp"

#include <memory>

#include "GuiStates/AttackingShipsState.hpp"
#include "GuiStates/CreateFieldState.hpp"
#include "GuiStates/MenuState.hpp"
#include "GuiStates/PlacingShipsState.hpp"

GameGui::GameGui() {
    window.create(sf::VideoMode(800, 600), "Battlefield 0");
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
            state = std::make_unique<PlacingShipsState>(player);
            break;
        case GameState::AttackingShips:
            currentState = newState;
            state = std::make_unique<AttackingShipsState>(player);
            break;
        case GameState::CreateField:
            currentState = newState;
            state = std::make_unique<CreateFieldState>(player);
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
