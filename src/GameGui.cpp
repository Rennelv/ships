#include "GameGui.hpp"

#include <memory>

#include "GuiStates/AttackingShipsState.hpp"
#include "GuiStates/CreateFieldState.hpp"
#include "GuiStates/MenuState.hpp"
#include "GuiStates/PlacingShipsState.hpp"

GameGui::GameGui() {
    size_t lengths[] = {4, 3, 2, 2, 1, 1};
    shipManager = std::make_unique<ShipManager>(6, lengths);
    abilityManager = std::make_unique<AbilityManager>();

    window.create(sf::VideoMode(800, 600), "Battlefield 0");
    window.setFramerateLimit(60);
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
            state = std::make_unique<PlacingShipsState>(*shipField, *shipManager);
            break;
        case GameState::AttackingShips:
            currentState = newState;
            state = std::make_unique<AttackingShipsState>(*shipField, *shipManager, *abilityManager);
            break;
        case GameState::CreateField:
            currentState = newState;
            state = std::make_unique<CreateFieldState>(shipField);
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

// void GameGui::drawField(ShipField& field, int x_offset, int y_offset, bool show_ships) {
//     window.clear();
//     sf::RectangleShape cellShape;
//     for (int y = 0; y < field.getHeight(); ++y) {
//         for (int x = 0; x < field.getWidth(); ++x) {
//             CellVisibilityState cellState = field.getCellVisibilityState(x, y);
//             if (show_ships) {
//                 cellState = field.getIsShip(x, y) ? CellVisibilityState::SHIP : CellVisibilityState::BLANK;
//             }
//             switch (cellState) {
//                 case CellVisibilityState::UNKNOWN:
//                     cellShape.setFillColor(sf::Color::Cyan);
//                     break;
//                 case CellVisibilityState::BLANK:
//                     cellShape.setFillColor(sf::Color::White);
//                     break;
//                 case CellVisibilityState::SHIP:
//                     switch (field.getShipSegmentState(x, y)) {
//                         case ShipSegmentState::INTACT:
//                             cellShape.setFillColor(sf::Color::Blue);
//                         case ShipSegmentState::DAMAGED:
//                             cellShape.setFillColor(sf::Color::Yellow);
//                         case ShipSegmentState::DESTROYED:
//                             cellShape.setFillColor(sf::Color::Red);
//                     }
//                     break;
//                 default:
//                     cellShape.setFillColor(sf::Color::Black);
//                     break;
//             }

//             cellShape.setPosition(x_offset + x * 30.f, y_offset + y * 30.f);
//             window.draw(cellShape);
//         }
//     }
// }
