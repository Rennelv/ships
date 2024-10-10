#include "Game.hpp"

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
