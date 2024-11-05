#include "Game.hpp"

#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Window/WindowStyle.hpp>

#include "Cli.hpp"

Game::Game() {
    field = nullptr;
    manager = nullptr;
}

Game::~Game() {
    delete field;
    delete manager;
}

void Game::run() {
    Cli cli = Cli();

    cli.createField(field);

    cli.printFieldExposed(*field);

    cli.createShips(manager);
    cli.placeShips(field, manager);

    cli.printFieldExposed(*field, true);

    while (manager->getAliveCount() > 0) {
        cli.attackShip(field);

        cli.printField(*field);
        cli.printAliveShips(manager);
    }
}

// void Game::runGui() {
//     Cli cli = Cli();

//     cli.createField(field);

//     cli.createShips(manager);
//     cli.placeShips(field, manager);

//     const int windowWidth = 1600;
//     const int windowHeight = 1200;
//     const int cellSize = 20;  // Size of each grid cell

//     // Create a window
//     sf::RenderWindow window(sf::VideoMode(windowWidth, windowHeight), "Sea Battle", sf::Style::Default);
//     sf::ContextSettings settings;
//     settings.antialiasingLevel = 8;
//     window.setFramerateLimit(60);

//     sf::Texture cellTexture;
//     cellTexture.loadFromFile("assets/sprites/chisato.jpg");

//     // Main game loop
//     while (window.isOpen()) {
//         // Event handling
//         sf::Event event;
//         while (window.pollEvent(event)) {
//             if (event.type == sf::Event::Closed) {
//                 window.close();
//             }

//             // Mouse click handling
//             if (event.type == sf::Event::MouseButtonPressed) {
//                 if (event.mouseButton.button == sf::Mouse::Left) {
//                     int x = event.mouseButton.x / cellSize;
//                     int y = event.mouseButton.y / cellSize;
//                     try {
//                         field->attackShip(x, y);
//                     } catch (std::invalid_argument &e) {
//                         // Handle invalid attack
//                     }
//                 }
//             }
//         }

//         // Clear the window
//         window.clear();

//         // Draw the game grid
//         for (int i = 0; i < field->getWidth(); ++i) {
//             for (int j = 0; j < field->getHeight(); ++j) {
//                 sf::Sprite cell(cellTexture);
//                 cell.setScale(static_cast<float>(cellSize) / cellTexture.getSize().x, static_cast<float>(cellSize) / cellTexture.getSize().y);

//                 cell.setPosition(i * cellSize, j * cellSize);

//                 // Set cell color based on its state
//                 if (field->getCellVisibilityState(i, j) == CellVisibilityState::UNKNOWN) {
//                     cell.setColor(sf::Color::Blue);  // Hidden cells
//                 } else if (field->getCellVisibilityState(i, j) == CellVisibilityState::BLANK) {
//                     cell.setColor(sf::Color::White);  // Empty cells
//                 } else {
//                     const ShipSegmentState &segment_state = field->getShipSegmentState(i, j);
//                     if (segment_state == ShipSegmentState::DESTROYED) {
//                         cell.setColor(sf::Color::Red);  // Destroyed ship
//                     } else {
//                         cell.setColor(sf::Color::Green);  // Ship segment
//                     }
//                 }

//                 window.draw(cell);
//             }
//         }

//         // Display the contents
//         window.display();
//     }
// }
