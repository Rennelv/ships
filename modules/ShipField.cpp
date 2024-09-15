// ShipField.cpp

#include "ShipField.hpp"

#include <iostream>

#include "Ship.hpp"

ShipField::ShipField(int new_width, int new_height) {
    width = new_width;
    height = new_height;
    field = new Ship::Segment **[height];
    for (int i = 0; i < height; i++) {  // i for height and j for width
        field[i] = new Ship::Segment *[width];
        for (int j = 0; j < width; j++) {
            field[i][j] = nullptr;  // 0 means empty cell
        }
    }  // 0 0 is the bottom left corner
}

void ShipField::setManager(ShipManager *new_manager) {
    manager = new_manager;
}

ShipField::~ShipField() {
    for (int i = 0; i < height; i++) {
        delete[] field[i];
    }
    delete[] field;
}

bool ShipField::placeShip(Ship *ship, int x, int y,
                          Ship::Orientation orientation) {
    int length = ship->getLenght();
    if (orientation ==
        Ship::HORIZONTAL) {  // horizontal placement of the ship on the field
        if (x < 0 || x + length >= width) {  // 0 0 is the bottom left corner
            return false;
        }
        if (y < 0 || y >= height) {
            return false;
        }
        for (int i = x - 1; i < (x + length) + 1; i++) {
            for (int j = y - 1; j < y + 2; j++) {
                if (i >= width || j >= height || i < 0 || j < 0) {
                    continue;
                }
                if (field[j][i] != nullptr) {
                    return false;
                }
            }
        }
        manager->addNewShip(length);
        for (int i = x; i < x + length; i++) {
            field[y][i] =
                manager->getShip(manager->getCount() - 1)->getSegment(i - y);
            ;  // ship segment
        }
    } else {  // vertical placement of the ship on the field
        if (x < 0 || x >= width) {
            return false;
        }
        if (y < 0 || y + length >= height) {
            return false;
        }
        for (int i = x - 1; i < x + 2; i++) {
            for (int j = y - 1; j < (y + length) + 1; j++) {
                if (i >= width || j >= height || i < 0 || j < 0) {
                    continue;
                }
                if (field[j][i] != 0) {
                    return false;
                }
            }
        }
        manager->addNewShip(length);
        for (int i = y; i < y + length; i++) {
            field[i][x] =
                manager->getShip(manager->getCount() - 1)->getSegment(i - y);
        }
    }
    return true;
}

bool ShipField::placeNewShip(int length, int x, int y,
                             Ship::Orientation orientation) {
    if (orientation ==
        Ship::HORIZONTAL) {  // horizontal placement of the ship on the field
        if (x < 0 || x + length >= width) {  // 0 0 is the bottom left corner
            return false;
        }
        if (y < 0 || y >= height) {
            return false;
        }
        for (int i = x - 1; i < (x + length) + 1; i++) {
            for (int j = y - 1; j < y + 2; j++) {
                if (i >= width || j >= height || i < 0 || j < 0) {
                    continue;
                }
                if (field[j][i] != nullptr) {
                    return false;
                }
            }
        }
        manager->addNewShip(length);
        for (int i = x; i < x + length; i++) {
            field[y][i] =
                manager->getShip(manager->getCount() - 1)->getSegment(i - y);
            ;  // ship segment
        }
    } else {  // vertical placement of the ship on the field
        if (x < 0 || x >= width) {
            return false;
        }
        if (y < 0 || y + length >= height) {
            return false;
        }
        for (int i = x - 1; i < x + 2; i++) {
            for (int j = y - 1; j < (y + length) + 1; j++) {
                if (i >= width || j >= height || i < 0 || j < 0) {
                    continue;
                }
                if (field[j][i] != 0) {
                    return false;
                }
            }
        }
        manager->addNewShip(length);
        for (int i = y; i < y + length; i++) {
            field[i][x] =
                manager->getShip(manager->getCount() - 1)->getSegment(i - y);
        }
    }
    return true;
}

bool ShipField::checkPlace(int x, int y) {
    if (x < 0 || x >= width || y < 0 || y >= height) {
        return false;
    }
    return field[y][x] != nullptr;
}

void ShipField::printField() {
    for (int i = height - 1; i >= 0; i--) {
        std::cout << i << " ";
        for (int j = 0; j < width; j++) {
            if (this->checkPlace(j, i)) {
                if (!field[i][j]->getBelongsTo()->isAlive()) {
                    std::cout << "X ";
                } else {
                    std::cout << field[i][j]->getHp() << " ";
                }
            } else {
                std::cout << ". ";
            }
        }
        std::cout << std::endl;
    }
    std::cout << "  ";
    for (int i = 0; i < width; i++) {
        std::cout << i << " ";
    }
    std::cout << std::endl;
}

bool ShipField::attackShip(int x, int y) {
    if (x < 0 || x >= width || y < 0 || y >= height) {
        return false;
    }
    if (field[y][x] == nullptr) {
        return false;
    }
    if (field[y][x]->getHp() <= 0) {
        return false;
    }
    field[y][x]->damage(1);
    return true;
}
