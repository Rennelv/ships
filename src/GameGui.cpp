#include "GameGui.hpp"

#include <memory>

#include "GuiStates/AttackingShipsState.hpp"
#include "GuiStates/CreateFieldState.hpp"
#include "GuiStates/CreateShipsState.hpp"
#include "GuiStates/MenuState.hpp"
#include "GuiStates/PlacingShipsState.hpp"

GameGui::GameGui(const Game &game) : game(game) {
    window.create(sf::VideoMode(1600, 900), "Battlefield 0", sf::Style::Close | sf::Style::Titlebar);
    window.setFramerateLimit(60);
    // sf::ContextSettings settings;
    // settings.antialiasingLevel = 8;
    state = std::make_unique<MenuState>();
}

void GameGui::changeState() {
    switch (game.getCurrentStage()) {
        case Stage::NOT_STARTED:
            state = std::make_unique<MenuState>();
            break;
        case Stage::CREATING_FIELD:
            state = std::make_unique<CreateFieldState>(game.getPlayer());
            break;
        case Stage::CREATING_SHIPS:
            state = std::make_unique<CreateShipState>(game.getPlayer());
            break;
        case Stage::PLACING_SHIPS:
            state = std::make_unique<PlacingShipsState>(game.getPlayer());
            break;
        case Stage::PLAYER_TURN:
        case Stage::AI_TURN:
            state = std::make_unique<AttackingShipsState>(game.getPlayer(), game.getAiController().getPlayer());
            break;
        case Stage::EXIT:
            window.close();
            break;
        default:
            break;
    }
}

void GameGui::pollEvents() {
    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            // changeState(GuiStates::Exit);

            break;
        }
        // state->handleInput(event);
    }
}

void GameGui::update() {
    pollEvents();
    state->update();
    // if (state->changeState() != current_state) {
    //     changeState(state->changeState());
    // }
}

void GameGui::render() {
    changeState();
    state->render(window);
}

void GameGui::mainLoop() {
    while (window.isOpen()) {
        update();
        render();
    }
}

void GameGui::run() {
    mainLoop();
}
