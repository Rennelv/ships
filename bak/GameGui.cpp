#include "GameGui.hpp"

#include <memory>

#include "GuiStates/AttackingShipsState.hpp"
#include "GuiStates/CreateFieldState.hpp"
#include "GuiStates/CreateShipsState.hpp"
#include "GuiStates/GameStates.hpp"
#include "GuiStates/MenuState.hpp"
#include "GuiStates/PlacingShipsState.hpp"
#include "GuiStates/SaveLoadState.hpp"

GameGui::GameGui(Game &game) : game(game) {
    window.create(sf::VideoMode(1600, 900), "Battlefield 0", sf::Style::Close | sf::Style::Titlebar);
    window.setFramerateLimit(60);
    // sf::ContextSettings settings;
    // settings.antialiasingLevel = 8;
    current_state = GuiStates::Menu;
    prev_state = GuiStates::Menu;
    changeState(GuiStates::Menu);
}

GuiStates GameGui::getCurrentState() const {
    return current_state;
}

GuiStates GameGui::getPrevState() const {
    return prev_state;
}

void GameGui::changeState() {
    switch (game.getCurrentStage()) {
        case Stage::CREATING_FIELD:
            changeState(GuiStates::CreateField);
            break;
        case Stage::CREATING_SHIPS:
            changeState(GuiStates::CreateShips);
            break;
        case Stage::PLACING_SHIPS:
            changeState(GuiStates::PlacingShips);
            break;
        case Stage::PLAYER_TURN:
            changeState(GuiStates::AttackingShips);
            break;
        case Stage::AI_TURN:
            changeState(GuiStates::AttackingShips);
            break;
        case Stage::NOT_STARTED:
            changeState(GuiStates::Menu);
            break;
        default:
            break;
    }
}

void GameGui::changeState(GuiStates new_state) {
    switch (new_state) {
        case GuiStates::Menu:
            if (current_state == GuiStates::Menu) return;
            prev_state = current_state;
            current_state = new_state;
            state = std::make_unique<MenuState>();
            break;
        case GuiStates::PlacingShips:
            if (current_state == GuiStates::PlacingShips) return;
            prev_state = current_state;
            current_state = new_state;
            state = std::make_unique<PlacingShipsState>(game);
            break;
        case GuiStates::AttackingShips:
            if (current_state == GuiStates::AttackingShips) return;
            prev_state = current_state;
            current_state = new_state;
            state = std::make_unique<AttackingShipsState>(game);
            break;
        case GuiStates::CreateField:
            if (current_state == GuiStates::CreateField) return;
            prev_state = current_state;
            current_state = new_state;
            state = std::make_unique<CreateFieldState>(game);
            break;
        case GuiStates::CreateShips:
            if (current_state == GuiStates::CreateShips) return;
            prev_state = current_state;
            current_state = new_state;
            state = std::make_unique<CreateShipState>(game);
            break;
        case GuiStates::Exit:
            if (current_state == GuiStates::Exit) return;
            window.close();
            break;
        case GuiStates::SaveLoadState:
            if (current_state == GuiStates::SaveLoadState) return;
            prev_state = current_state;
            current_state = new_state;
            state = std::make_unique<SaveLoadState>(game);
            break;
    }
}

void GameGui::pollEvents() {
    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            changeState(GuiStates::Exit);
            break;
        }
        state->handleInput(event);
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

void GameGui::aaaaaaaaa() {
    changeState();
    update();
    render();
}

void GameGui::run() {
    mainLoop();
}
