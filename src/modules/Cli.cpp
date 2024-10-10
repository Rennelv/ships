#include "Cli.hpp"

#include <iostream>
#include <limits>

#include "Enums.hpp"

void Cli::printField(const ShipField &field) const {
    const size_t height = field.getHeight();
    const size_t width = field.getWidth();
    for (int y = height - 1; y >= 0; y--) {
        std::cout << y << (height <= 10 ? " " : ((y < 10) ? "  " : " "));
        for (size_t x = 0; x < width; x++) {
            if (field.getCellVisibilityState(x, y) == CellVisibilityState::UNKNOWN) {
                std::cout << ((width > 10) ? ".  " : ". ");
            } else if (field.getCellVisibilityState(x, y) == CellVisibilityState::BLANK) {
                std::cout << ((width > 10) ? "O  " : "O ");
            } else {
                const ShipSegmentState &segment_state = field.getShipSegmentState(x, y);
                if (segment_state == ShipSegmentState::DESTROYED) {
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

void Cli::printFieldExposed(const ShipField &field, bool show_hp) const {
    const size_t height = field.getHeight();
    const size_t width = field.getWidth();
    for (int y = height - 1; y >= 0; y--) {
        std::cout << y << (height <= 10 ? " " : ((y < 10) ? "  " : " "));
        for (size_t x = 0; x < width; x++) {
            if (field.getIsShip(x, y)) {
                const int &segment_hp = field.getShipSegmentHP(x, y);
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

void Cli::createField(ShipField *&field) {
    int width, height;
    while (field == nullptr) {
        std::cout << "Write field size (x,y): \n";
        std::cin >> width >> height;
        if (std::cin.fail()) {
            std::cin.clear();                                                    // Clear the error state
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');  // Ignore invalid input
            std::cout << "Invalid input. Please enter integers for width and height.\n";
            continue;
        }
        try {
            field = new ShipField(width, height);
        } catch (std::exception &e) {
            std::cout << e.what() << '\n';
            std::cout << "Try again \n";
        }
    }
}

void Cli::createShips(ShipManager *&manager) {
    std::vector<size_t> lengths;
    lengths.reserve(10);
    for (size_t i = 4; i > 0; i--) {
        std::cout << "Write how many ships of length " << i << " you want: ";
        int count;
        std::cin >> count;
        if (std::cin.fail() || count < 0) {
            std::cin.clear();                                                    // Clear the error state
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');  // Ignore invalid input
            std::cout << "Invalid input. Please enter a non-negative integer.\n";
            i++;  // Retry the current length
            continue;
        }
        for (int j = 0; j < count; j++) {
            lengths.push_back(i);
        }
    }

    manager = new ShipManager(lengths.size(), lengths.data());
}

void Cli::placeShips(ShipField *&field, ShipManager *&manager) {
    std::cout << "Place ships on the field\n";
    for (size_t i = 0; i < manager->getShipCount(); i++) {
        const size_t ship_length = manager->getShip(i)->getLenght();
        int x, y;
        std::cout << "Write x and y for ship " << i << " of length " << ship_length << " (bottom left corner): ";
        std::cin >> x >> y;
        if (std::cin.fail() || x < 0 || y < 0) {
            std::cin.clear();                                                    // Clear the error state
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');  // Ignore invalid input
            std::cout << "Invalid input. Please enter non-negative integers for coordinates.\n";
            i--;  // Retry the current ship
            continue;
        }
        ShipOrientation orientation;
        if (ship_length == 1) {
            orientation = ShipOrientation::HORIZONTAL;
        } else {
            std::cout << "Write orientation for ship " << i << " (0 - HORIZONTAL, 1 - VERTICAL): ";
            int ori;
            std::cin >> ori;
            if (std::cin.fail() || (ori != 0 && ori != 1)) {
                std::cin.clear();                                                    // Clear the error state
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');  // Ignore invalid input
                std::cout << "Invalid input. Please enter 0 for HORIZONTAL or 1 for VERTICAL.\n";
                i--;  // Retry the current ship
                continue;
            }
            orientation = (ori == 0) ? ShipOrientation::HORIZONTAL : ShipOrientation::VERTICAL;
        }
        try {
            field->placeShip(manager->getShip(i), x, y, orientation);
        } catch (std::invalid_argument &e) {
            std::cout << "Can't place ship there. Try again\n";
            i--;
            continue;
        }
        printFieldExposed(*field);
    }
}

void Cli::attackShip(ShipField *&field) {
    int x, y;
    std::cout << "Write x and y for attack: \n";
    std::cin >> x >> y;
    if (std::cin.fail() || x < 0 || y < 0) {
        std::cin.clear();                                                    // Clear the error state
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');  // Ignore invalid input
        std::cout << "Invalid input. Please enter non-negative integers for coordinates.\n";
        return;  // Exit the function to allow the user to try again
    }
    field->attackShip(x, y);
}

void Cli::printAliveShips(ShipManager *&manager) const {
    std::cout << "Alive ships: " << manager->getAliveCount() << '\n';
}