#include "Game.hpp"

#include <cstddef>
#include <exception>
#include <iostream>

Game::Game() {
    field = nullptr;
    manager = nullptr;
}

Game::~Game() {
    delete field;
    delete manager;
}

void Game::run() {
    int width, height;
    while (field == nullptr) {
        std::cout << "Write field size (x,y): \n";
        std::cin >> width >> height;
        try {
            field = new ShipField(width, height);
        } catch (std::exception &e) {
            std::cout << e.what() << '\n';
            std::cout << "Try again \n";
        };
    }

    printFieldExposed(field);

    std::vector<size_t> lengths;
    lengths.reserve(10);
    for (size_t i = 4; i > 0; i--) {
        std::cout << "Write how many ships of length " << i << " you want: ";
        int count;
        std::cin >> count;
        for (int j = 0; j < count; j++) {
            lengths.push_back(i);
        }
    }

    ShipManager *manager = new ShipManager(lengths.size(), lengths);

    std::cout << "Place ships on the field\n";
    for (size_t i = 0; i < manager->getShipCount(); i++) {
        int x, y;
        std::cout << "Write x and y for ship " << i << " of length " << lengths[i] << " (bottom left corner): ";
        std::cin >> x >> y;
        Ship::Orientation orientation;
        if (lengths[i] == 1) {
            orientation = Ship::Orientation::HORIZONTAL;
        } else {
            std::cout << "Write orientation for ship " << i << " (0 - HORIZONTAL, 1 - VERTICAL): ";
            int ori;
            std::cin >> ori;
            if (ori == 0) {
                orientation = Ship::Orientation::HORIZONTAL;
            } else {
                orientation = Ship::Orientation::VERTICAL;
            }
        }
        try {
            field->placeShip(manager->getShip(i), x, y, orientation);
        } catch (std::invalid_argument &e) {
            std::cout << "Can't place ship on the field\n";
            i--;
            continue;
        }
        printFieldExposed(field);
    }

    // ShipField *field2 = new ShipField(*field);              // Use copy constructor
    // ShipField *field3 = new ShipField(*field);              // Use copy constructor
    // ShipField *field4 = new ShipField(std::move(*field3));  // Use move constructor
    // field2->clearField();

    printFieldExposed(field, true);
    while (manager->getAliveCount() > 0) {
        int x, y;
        std::cout << "Write x and y for attack: \n";
        std::cin >> x >> y;
        field->attackShip(x, y);
        printField(field);
        std::cout << "Alive ships: " << manager->getAliveCount() << '\n';
        // print_field(field2);
        // print_field_exposed(field4);
    }
}

void Game::printField(const ShipField *field) {
    const size_t height = field->getHeight();
    const size_t width = field->getWidth();
    for (int y = height - 1; y >= 0; y--) {
        std::cout << y << (height <= 10 ? " " : ((y < 10) ? "  " : " "));
        for (size_t x = 0; x < width; x++) {
            if (field->getCellVisibilityState(x, y) == ShipField::CellVisibilityState::UNKNOWN) {
                std::cout << ((width > 10) ? ".  " : ". ");
            } else if (field->getCellVisibilityState(x, y) == ShipField::CellVisibilityState::BLANK) {
                std::cout << ((width > 10) ? "O  " : "O ");
            } else {
                const Ship::SegmentState &segment_state = field->getShipSegmentState(x, y);
                if (segment_state == Ship::SegmentState::DESTROYED) {
                    std::cout << ((width > 10) ? "X  " : "X ");
                } else {
                    std::cout << ((width > 10) ? "/  " : "/ ");
                }
            }
        }
        std::cout << std::endl;
    }
    std::cout << (height > 10 ? "   " : "  ");
    for (size_t i = 0; i < width; i++) {
        std::cout << i << (width <= 10 ? " " : ((i < 9) ? "  " : " "));
    }
    std::cout << std::endl;
}

void Game::printFieldExposed(const ShipField *field, bool show_hp) {
    const size_t height = field->getHeight();
    const size_t width = field->getWidth();
    for (int y = height - 1; y >= 0; y--) {
        std::cout << y << (height <= 10 ? " " : ((y < 10) ? "  " : " "));
        for (size_t x = 0; x < width; x++) {
            if (field->getIsShip(x, y)) {
                const int &segment_hp = field->getShipSegmentHP(x, y);
                std::cout << (show_hp ? std::to_string(segment_hp) : "P") << ((width > 10) ? "  " : " ");
            } else {
                std::cout << "." << ((width > 10) ? "  " : " ");
            }
        }
        std::cout << std::endl;
    }
    std::cout << (height > 10 ? "   " : "  ");
    for (size_t i = 0; i < width; i++) {
        std::cout << i << (width <= 10 ? " " : ((i < 9) ? "  " : " "));
    }
    std::cout << std::endl;
}