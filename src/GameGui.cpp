#include "GameGui.hpp"

#include <memory>

#include "GuiStates/AttackingShipsState.hpp"
#include "GuiStates/CreateFieldState.hpp"
#include "GuiStates/CreateShipsState.hpp"
#include "GuiStates/MenuState.hpp"
#include "GuiStates/PlacingShipsState.hpp"

Gui::Gui(const Game &game) : game(game) {
    window.create(sf::VideoMode(1600, 900), "Battlefield 0", sf::Style::Close | sf::Style::Titlebar);
    window.setFramerateLimit(60);
    // sf::ContextSettings settings;
    // settings.antialiasingLevel = 8;
    state = std::make_unique<MenuState>();
    prevStage = game.getCurrentStage();
}

void Gui::changeState() {
    if (prevStage == game.getCurrentStage()) {
        return;
    }
    prevStage = game.getCurrentStage();
    switch (game.getCurrentStage()) {
        case Stage::NOT_STARTED:
            state = std::make_unique<MenuState>();
            break;
        case Stage::CREATING_FIELD:
            state = std::make_unique<CreateFieldState>(game);
            break;
        case Stage::CREATING_SHIPS:
            state = std::make_unique<CreateShipState>(game);
            break;
        case Stage::PLACING_SHIPS:
            state = std::make_unique<PlacingShipsState>(game);
            break;
        case Stage::PLAYER_TURN:
        case Stage::AI_TURN:
            state = std::make_unique<AttackingShipsState>(game);
            break;
        case Stage::EXIT:
            window.close();
            break;
        default:
            break;
    }
}

// void Gui::pollEvents() {
//     while (window.pollEvent(event)) {
//         if (event.type == sf::Event::Closed) {
//             // changeState(GuiStates::Exit);

//             break;
//         }
//         // state->handleInput(event);
//     }
// }

// void Gui::update() {
//     // pollEvents();
//     state->update();
//     // if (state->changeState() != current_state) {
//     //     changeState(state->changeState());
//     // }
// }

void Gui::render() {
    changeState();
    state->render(window);
}

// void Gui::mainLoop() {
//     while (window.isOpen()) {
//         update();
//         render();
//     }
// }

// void Gui::run() {
//     mainLoop();
// }

void Gui::printErr(std::string msg) {
    state->printErr(msg);
}
