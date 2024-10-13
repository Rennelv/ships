#include "GameGui.hpp"

#include "AttackingShipsState.hpp"
#include "CreateFieldState.hpp"
#include "MenuState.hpp"
#include "PlacingShipsState.hpp"

GameGui::GameGui() : currentState(GameState::Menu) {
    size_t lengths[] = {4, 3, 2, 2, 1, 1};
    shipManager = new ShipManager(6, lengths);

    window.create(sf::VideoMode(800, 600), "Battlefield 0");
    changeState(GameState::Menu);
}

GameGui::~GameGui() {
    delete shipField;
    delete shipManager;
    window.close();
}

void GameGui::changeState(GameState newState) {
    currentState = newState;
    switch (currentState) {
        case GameState::Menu:
            state = std::make_unique<MenuState>();
            break;
        case GameState::PlacingShips:
            state = std::make_unique<PlacingShipsState>(*shipField, *shipManager);
            break;
        case GameState::AttackingShips:
            state = std::make_unique<AttackingShipsState>(*shipField, *shipManager);
            break;
        case GameState::CreateField:
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
            window.close();
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

void GameGui::drawField(ShipField& field, int x_offset, int y_offset, bool show_ships) {
    window.clear();
    sf::RectangleShape cellShape;
    for (int y = 0; y < field.getHeight(); ++y) {
        for (int x = 0; x < field.getWidth(); ++x) {
            CellVisibilityState cellState = field.getCellVisibilityState(x, y);
            if (show_ships) {
                cellState = field.getIsShip(x, y) ? CellVisibilityState::SHIP : CellVisibilityState::BLANK;
            }
            switch (cellState) {
                case CellVisibilityState::UNKNOWN:
                    cellShape.setFillColor(sf::Color::Cyan);
                    break;
                case CellVisibilityState::BLANK:
                    cellShape.setFillColor(sf::Color::White);
                    break;
                case CellVisibilityState::SHIP:
                    switch (field.getShipSegmentState(x, y)) {
                        case ShipSegmentState::INTACT:
                            cellShape.setFillColor(sf::Color::Blue);
                        case ShipSegmentState::DAMAGED:
                            cellShape.setFillColor(sf::Color::Yellow);
                        case ShipSegmentState::DESTROYED:
                            cellShape.setFillColor(sf::Color::Red);
                    }
                    break;
                default:
                    cellShape.setFillColor(sf::Color::Black);
                    break;
            }

            cellShape.setPosition(x_offset + x * 30.f, y_offset + y * 30.f);
            window.draw(cellShape);
        }
    }
}
