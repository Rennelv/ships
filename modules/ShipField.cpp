// ShipField.cpp

#include "ShipField.hpp"

#include <iostream>

#include "Ship.hpp"

ShipField::ShipField(int new_width, int new_height) {
    width = new_width;
    height = new_height;
    field = new FieldElement *[height];
    for (int i = 0; i < height; i++) {  // i for height and j for width
        field[i] = new FieldElement[width];
        for (int j = 0; j < width; j++) {
            field[i][j] = FieldElement{FieldElement::VisibilityState::UNKNOWN, j, i, nullptr, false, -1, -1};
        }
    }  // 0 0 is the bottom left corner
}

// void ShipField::setManager(ShipManager *new_manager) {
//     manager = new_manager;
// }

ShipField::~ShipField() {
    for (int i = 0; i < height; i++) {
        delete[] field[i];
    }
    delete[] field;
}

bool ShipField::placeShip(Ship *ship, int x, int y, Ship::Orientation orientation) {
    int length = ship->getLenght();
    if (orientation == Ship::HORIZONTAL) {   // horizontal placement of the ship on the field
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
                if (field[j][i].is_ship == true) {
                    return false;
                }
            }
        }
        for (int i = x; i < x + length; i++) {
            field[y][i].ship_index = ship->getShipIndex();
            field[y][i].ship = ship;
            field[y][i].segment_index = i - x;
            field[y][i].is_ship = true;
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
                if (field[j][i].is_ship == true) {
                    return false;
                }
            }
        }
        for (int i = y; i < y + length; i++) {
            field[i][x].ship_index = ship->getShipIndex();
            field[i][x].ship = ship;
            field[i][x].segment_index = i - y;
            field[i][x].is_ship = true;
        }
    }
    return true;
}

bool ShipField::checkPlace(int x, int y) {
    if (x < 0 || x >= width || y < 0 || y >= height) {
        return false;
    }
    return field[y][x].is_ship;
}

void ShipField::printField(bool expose_ships) {
    for (int i = height - 1; i >= 0; i--) {
        std::cout << i << " ";
        for (int j = 0; j < width; j++) {
            if (expose_ships) {
                if (this->checkPlace(j, i)) {
                    if (!field[i][j].ship->isAlive()) {
                        std::cout << "X ";
                    } else {
                        std::cout << field[i][j].ship->getSegment(field[i][j].segment_index)->hp << " ";
                    }
                } else {
                    std::cout << ". ";
                }
            } else {
                if (field[i][j].state == FieldElement::VisibilityState::UNKNOWN) {
                    std::cout << ". ";
                } else if (field[i][j].state == FieldElement::VisibilityState::BLANK) {
                    std::cout << "O ";
                } else {
                    if (field[i][j].ship->getSegment(field[i][j].segment_index)->hp == 0) {
                        std::cout << "X ";
                    } else {
                        std::cout << "/ ";
                    }
                }
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

    if (field[y][x].is_ship == false) {
        field[y][x].state = FieldElement::VisibilityState::BLANK;
        return false;
    }
    Ship *current = field[y][x].ship;
    if (current->getSegment(field[y][x].segment_index)->hp <= 0) {
        return false;
    }
    field[y][x].state = FieldElement::VisibilityState::SHIP;
    current->takeDamage(field[y][x].segment_index, 1);
    return true;
}
