// ShipField.cpp

#include "ShipField.hpp"

#include "Ship.hpp"

ShipField::ShipField(int width, int height) {
    this->width = width;
    this->height = height;
    field = new FieldElement *[height];
    for (int i = 0; i < height; i++) {  // i for height and j for width
        field[i] = new FieldElement[width];
        for (int j = 0; j < width; j++) {
            field[i][j] = FieldElement{FieldElement::VisibilityState::UNKNOWN, j, i, nullptr, false, -1, -1};
        }
    }  // 0 0 is the bottom left corner
}

ShipField::~ShipField() {
    for (int i = 0; i < height; i++) {
        delete[] field[i];
    }
    delete[] field;
}

ShipField::ShipField(const ShipField &other) {
    this->width = other.width;
    this->height = other.height;
    field = new FieldElement *[height];
    for (int i = 0; i < height; i++) {
        field[i] = new FieldElement[width];
        for (int j = 0; j < width; j++) {
            field[i][j] = other.field[i][j];
            if (other.field[i][j].is_ship) {
                field[i][j].ship = new Ship(*other.field[i][j].ship);
            } else {
                field[i][j].ship = nullptr;
            }
        }
    }
}

ShipField::ShipField(ShipField &&other) noexcept {
    this->width = other.width;
    this->height = other.height;
    field = other.field;
    other.field = nullptr;
}

ShipField &ShipField::operator=(const ShipField &other) {
    if (this != &other) {
        for (int i = 0; i < height; i++) {
            delete[] field[i];
        }
        delete[] field;
        this->width = other.width;
        this->height = other.height;
        field = new FieldElement *[height];
        for (int i = 0; i < height; i++) {
            field[i] = new FieldElement[width];
            for (int j = 0; j < width; j++) {
                field[i][j] = other.field[i][j];
                if (other.field[i][j].is_ship) {
                    field[i][j].ship = new Ship(*other.field[i][j].ship);
                } else {
                    field[i][j].ship = nullptr;
                }
            }
        }
    }
    return *this;
}

ShipField &ShipField::operator=(ShipField &&other) noexcept {
    if (this != &other) {
        for (int i = 0; i < height; i++) {
            delete[] field[i];
        }
        delete[] field;
        this->width = other.width;
        this->height = other.height;
        field = other.field;
        other.field = nullptr;
    }
    return *this;
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


bool ShipField::attackShip(int x, int y) {
    if (x < 0 || x >= width || y < 0 || y >= height) {
        return false;
    }

    if (field[y][x].is_ship == false) {
        field[y][x].state = FieldElement::VisibilityState::BLANK;
        return false;
    }
    Ship *current = field[y][x].ship;
    if (current->getSegment(field[y][x].segment_index).hp <= 0) {
        return false;
    }
    field[y][x].state = FieldElement::VisibilityState::SHIP;
    current->takeDamage(field[y][x].segment_index, 1);
    return true;
}


int ShipField::getWidth() {
    return width;
}

int ShipField::getHeight() {
    return height;
}

FieldElement ShipField::getCell(int x, int y) {
    return field[y][x];
}