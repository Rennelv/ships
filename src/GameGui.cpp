#include "GameGui.hpp"

#include <istream>
#include <memory>

#include "GuiStates/AttackingShipsState.hpp"
#include "GuiStates/CreateFieldState.hpp"
#include "GuiStates/CreateShipsState.hpp"
#include "GuiStates/GameStates.hpp"
#include "GuiStates/MenuState.hpp"
#include "GuiStates/PlacingShipsState.hpp"
#include "GuiStates/SaveLoadState.hpp"
#include "Player.hpp"

GameGui::GameGui() : player(), player2(), ai_controller(player2) {
    window.create(sf::VideoMode(1600, 900), "Battlefield 0", sf::Style::Close | sf::Style::Titlebar);
    window.setFramerateLimit(60);
    // sf::ContextSettings settings;
    // settings.antialiasingLevel = 8;
    current_state = GameState::Menu;
    prev_state = GameState::Menu;
    changeState(GameState::Menu);
}

GameState GameGui::getCurrentState() const {
    return current_state;
}

GameState GameGui::getPrevState() const {
    return prev_state;
}

void GameGui::changeState(GameState new_state) {
    switch (new_state) {
        case GameState::Menu:
            prev_state = current_state;
            current_state = new_state;
            state = std::make_unique<MenuState>();
            break;
        case GameState::PlacingShips:
            prev_state = current_state;
            current_state = new_state;
            state = std::make_unique<PlacingShipsState>(player, ai_controller);
            break;
        case GameState::AttackingShips:
            prev_state = current_state;
            current_state = new_state;
            state = std::make_unique<AttackingShipsState>(player, ai_controller);
            break;
        case GameState::CreateField:
            prev_state = current_state;
            current_state = new_state;
            state = std::make_unique<CreateFieldState>(player, ai_controller);
            break;
        case GameState::CreateShips:
            prev_state = current_state;
            current_state = new_state;
            state = std::make_unique<CreateShipState>(player, ai_controller);
            break;
        case GameState::Exit:
            window.close();
            break;
        case GameState::SaveLoadState:
            prev_state = current_state;
            current_state = new_state;
            state = std::make_unique<SaveLoadState>(*this);
            break;
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
    if (state->changeState() != current_state) {
        changeState(state->changeState());
    }
}

void GameGui::render() {
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

std::ostream& operator<<(std::ostream& os, const GameGui& state) {
    os << "+++===GameGui===+++\n";
    os << state.player;
    os << state.player2;
    os << static_cast<int>(state.prev_state) << '\n';
    os << "+++===End GameGui===+++\n";
    return os;
}

std::istream& operator>>(std::istream& is, GameGui& state) {
    std::string line;
    is >> std::ws;
    std::getline(is, line);
    if (line != "+++===GameGui===+++") {
        throw std::invalid_argument("Invalid save file");
    }
    is >> state.player;
    is >> state.player2;
    int current_state;
    is >> current_state;
    state.changeState(static_cast<GameState>(current_state));
    is >> std::ws;
    std::getline(is, line);
    if (line != "+++===End GameGui===+++") {
        throw std::invalid_argument("Invalid save file");
    }
    return is;
}