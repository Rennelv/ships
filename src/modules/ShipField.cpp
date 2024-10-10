// ShipField.cpp

#include "ShipField.hpp"

#include <cstddef>
#include <stdexcept>

#include "Enums.hpp"
#include "Ship.hpp"

ShipField::ShipField(int new_width, int new_height) {
    if (new_width <= 0 || new_height <= 0) {
        throw std::invalid_argument("Width and height must be greater than 0");
    }
    if (new_width > 100 || new_height > 100) {
        throw std::invalid_argument("Width and height must be less than 100");
    }
    width = static_cast<size_t>(new_width);
    height = static_cast<size_t>(new_height);
    field = new FieldElement *[height];
    for (size_t i = 0; i < height; i++) {  // i for height and j for width
        field[i] = new FieldElement[width];
        for (size_t j = 0; j < width; j++) {
            field[i][j] = FieldElement{};
        }
    }  // 0 0 is the bottom left corner
}

ShipField::~ShipField() {
    if (field == nullptr) {
        return;
    }
    for (size_t i = 0; i < height; i++) {
        delete[] field[i];
    }
    delete[] field;
}

ShipField::ShipField(const ShipField &other) {
    this->width = other.width;
    this->height = other.height;
    field = new FieldElement *[height];
    for (size_t i = 0; i < height; i++) {
        field[i] = new FieldElement[width];
        for (size_t j = 0; j < width; j++) {
            field[i][j] = other.field[i][j];
        }
    }
}

ShipField &ShipField::operator=(const ShipField &other) {
    if (this != &other) {
        for (size_t i = 0; i < height; i++) {
            delete[] field[i];
        }
        delete[] field;
        this->width = other.width;
        this->height = other.height;
        field = new FieldElement *[height];
        for (size_t i = 0; i < height; i++) {
            field[i] = new FieldElement[width];
            for (size_t j = 0; j < width; j++) {
                field[i][j] = other.field[i][j];
            }
        }
    }
    return *this;
}

ShipField::ShipField(ShipField &&other) noexcept {
    this->width = other.width;
    this->height = other.height;
    field = other.field;
    other.field = nullptr;
    other.width = 0;
    other.height = 0;
}

ShipField &ShipField::operator=(ShipField &&other) noexcept {
    if (this != &other) {
        for (size_t i = 0; i < height; i++) {
            delete[] field[i];
        }
        delete[] field;
        this->width = other.width;
        this->height = other.height;
        field = other.field;
        other.field = nullptr;
        other.width = 0;
        other.height = 0;
    }
    return *this;
}

bool ShipField::checkShipCollision(Ship *ship, int head_x, int head_y, ShipOrientation orientation) const {
    const int ship_length = ship->getLenght();

    if (orientation == ShipOrientation::HORIZONTAL) {
        if (head_x + ship_length > static_cast<int>(width)) {
            return true;
        }
        for (int i = head_x - 1; i < head_x + ship_length + 1; i++) {
            for (int j = head_y - 1; j < head_y + 2; j++) {
                if (i >= static_cast<int>(width) || j >= static_cast<int>(height) || i < 0 || j <= 0) {
                    continue;
                }
                if (getIsShip(i, j)) {
                    return true;  // cant place ship
                }
            }
        }
    } else {
        if (head_y + ship_length > static_cast<int>(height)) {
            return true;
        }
        for (int i = head_x; i < head_x + 2; i++) {
            for (int j = head_y; j < head_y + ship_length + 1; j++) {
                if (i >= static_cast<int>(width) || j >= static_cast<int>(height) || i < 0 || j < 0) {
                    continue;
                }
                if (getIsShip(i, j)) {
                    return true;  // cant place ship
                }
            }
        }
    }
    return false;
}

void ShipField::exposeSurroundingShipCells(Ship *ship, int x, int y) {
    ShipOrientation orientation;
    const int ship_length = ship->getLenght();

    // calculate orientation of the ship
    if (getIsShip(x, y - 1) || getIsShip(x, y + 1)) {
        orientation = ShipOrientation::VERTICAL;
    } else {
        orientation = ShipOrientation::HORIZONTAL;
    }

    // calculate head of the ship
    int head_x = x;
    int head_y = y;

    if (orientation == ShipOrientation::HORIZONTAL) {
        while (getIsShip(head_x - 1, head_y)) {
            head_x--;
        }
    } else {
        while (getIsShip(head_x, head_y - 1)) {
            head_y--;
        }
    }

    if (orientation == ShipOrientation::HORIZONTAL) {
        for (int i = head_x - 1; i < head_x + ship_length + 1; i++) {
            for (int j = head_y - 1; j < head_y + 2; j++) {
                if (i >= static_cast<int>(width) || j >= static_cast<int>(height) || i < 0 || j < 0) {
                    continue;
                }
                if (getIsShip(i, j)) {
                    continue;
                } else {
                    field[j][i].state = CellVisibilityState::BLANK;
                }
            }
        }
    } else {
        for (int i = head_x - 1; i < head_x + 2; i++) {
            for (int j = head_y - 1; j < head_y + ship_length + 1; j++) {
                if (i >= static_cast<int>(width) || j >= static_cast<int>(height) || i < 0 || j < 0) {
                    continue;
                }
                if (getIsShip(i, j)) {
                    continue;
                } else {
                    field[j][i].state = CellVisibilityState::BLANK;
                }
            }
        }
    }
}

void ShipField::placeShip(Ship *ship, int x, int y, ShipOrientation orientation) {
    const size_t ship_length = ship->getLenght();
    if (x < 0 || y < 0) {  // 0 0 is the bottom left corner
        throw std::invalid_argument("Coordinates must be non-negative");
    }

    const size_t x_size = static_cast<size_t>(x);
    const size_t y_size = static_cast<size_t>(y);

    if (y_size >= height || x_size >= width) {
        throw std::invalid_argument("Coordinates are out of field bounds");
    }

    if (checkShipCollision(ship, x_size, y_size, orientation)) {
        throw std::invalid_argument("Ship collides with another ship or borders");
    }

    if (orientation == ShipOrientation::HORIZONTAL) {  // horizontal placement of the ship on the field
        for (size_t i = x_size; i < x_size + ship_length; i++) {
            field[y_size][i].ship = ship;
            field[y_size][i].ship_segment_index = i - x_size;
            field[y_size][i].is_ship = true;
        }
    } else {  // vertical placement of the ship on the field
        for (size_t i = y_size; i < y_size + ship_length; i++) {
            field[i][x_size].ship = ship;
            field[i][x_size].ship_segment_index = i - y_size;
            field[i][x_size].is_ship = true;
        }
    }
}

void ShipField::attackShip(int x, int y, int damage) {
    if (x < 0 || y < 0) {
        return;
    }
    const size_t x_size = static_cast<size_t>(x);
    const size_t y_size = static_cast<size_t>(y);

    if (x_size >= width || y_size >= height) {
        return;
    }

    if (getIsShip(x_size, y_size) == false) {
        field[y_size][x_size].state = CellVisibilityState::BLANK;
        return;
    }

    Ship *current = field[y_size][x_size].ship;
    const size_t ship_segment_index = field[y_size][x_size].ship_segment_index;
    
    if (current->getSegmentHP(ship_segment_index) <= 0) {
        return;
    }

    field[y_size][x_size].state = CellVisibilityState::SHIP;
    current->takeDamage(ship_segment_index, damage);
    if (current->isAlive() == false) {
        exposeSurroundingShipCells(current, x_size, y_size);
    }
}

size_t ShipField::getWidth() const {
    return width;
}

size_t ShipField::getHeight() const {
    return height;
}

bool ShipField::getIsShip(int x, int y) const {
    if (x < 0 || y < 0) {
        return false;
    }
    if (static_cast<size_t>(x) >= width || static_cast<size_t>(y) >= height) {
        return false;
    }
    return (field[y][x].is_ship);
}

void ShipField::clearField() {
    for (size_t i = 0; i < height; i++) {
        for (size_t j = 0; j < width; j++) {
            field[i][j] = FieldElement{};
        }
    }
}

CellVisibilityState ShipField::getCellVisibilityState(int x, int y) const {
    if (x < 0 || y < 0) {
        throw std::invalid_argument("Coordinates must be non-negative");
    }
    if (static_cast<size_t>(x) >= width || static_cast<size_t>(y) >= height) {
        throw std::invalid_argument("Coordinates are out of field bounds");
    }
    return field[y][x].state;
}

int ShipField::getShipSegmentHP(int x, int y) const {
    if (x < 0 || y < 0) {
        throw std::invalid_argument("Coordinates must be non-negative");
    }
    if (static_cast<size_t>(x) >= width || static_cast<size_t>(y) >= height) {
        throw std::invalid_argument("Coordinates are out of field bounds");
    }
    if (getIsShip(x, y) == false) {
        throw std::logic_error("No ship at the given coordinates");
    }
    return field[y][x].ship->getSegmentHP(field[y][x].ship_segment_index);
}

ShipSegmentState ShipField::getShipSegmentState(int x, int y) const {
    if (x < 0 || y < 0) {
        throw std::invalid_argument("Coordinates must be non-negative");
    }
    if (static_cast<size_t>(x) >= width || static_cast<size_t>(y) >= height) {
        throw std::invalid_argument("Coordinates are out of field bounds");
    }
    if (getIsShip(x, y) == false) {
        throw std::logic_error("No ship at the given coordinates");
    }
    return field[y][x].ship->getSegmentState(field[y][x].ship_segment_index);
}