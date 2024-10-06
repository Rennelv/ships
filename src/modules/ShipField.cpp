// ShipField.cpp

#include "ShipField.hpp"

#include <cstddef>
#include <stdexcept>

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
            field[i][j] = FieldElement{ShipField::CellVisibilityState::UNKNOWN, nullptr, false, 0, 0};
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
    }
    return *this;
}

bool ShipField::placeShip(Ship *ship, int x, int y, Ship::Orientation orientation) {
    size_t ship_length = ship->getLenght();
    if (x < 0 || y < 0) {  // 0 0 is the bottom left corner
        return false;
    }
    size_t x_size = static_cast<size_t>(x);
    size_t y_size = static_cast<size_t>(y);
    if (y_size >= height || x_size >= width) {
        return false;
    }
    if (orientation == Ship::HORIZONTAL) {  // horizontal placement of the ship on the field
        if (x_size + ship_length > width) {
            return false;
        }
        for (size_t i = x_size; i < x_size + ship_length + 2; i++) {
            for (size_t j = y_size; j < y_size + 3; j++) {
                if (i >= width + 1 || j >= height + 1 || i == 0 || j == 0) {
                    continue;
                }
                if (field[j - 1][i - 1].is_ship == true) {
                    return false;
                }
            }
        }
        for (size_t i = x_size; i < x_size + ship_length; i++) {
            field[y_size][i].ship_index = ship->getShipIndex();
            field[y_size][i].ship = ship;
            field[y_size][i].ship_segment_index = i - x_size;
            field[y_size][i].is_ship = true;
        }
    } else {  // vertical placement of the ship on the field
        if (y_size + ship_length > height) {
            return false;
        }
        for (size_t i = x_size; i < x_size + 3; i++) {
            for (size_t j = y_size; j < (y_size + ship_length) + 2; j++) {
                if (i >= width + 1 || j >= height + 1 || i == 0 || j == 0) {
                    continue;
                }
                if (field[j-1][i-1].is_ship == true) {
                    return false;
                }
            }
        }
        for (size_t i = y_size; i < y_size + ship_length; i++) {
            field[i][x_size].ship_index = ship->getShipIndex();
            field[i][x_size].ship = ship;
            field[i][x_size].ship_segment_index = i - y_size;
            field[i][x_size].is_ship = true;
        }
    }
    return true;
}

bool ShipField::getIsShip(int x, int y) const {
    if (x < 0 || y < 0) {
        return false;
    }
    if (static_cast<size_t>(x) >= width || static_cast<size_t>(y) >= height) {
        return false;
    }
    return field[y][x].is_ship;
}

bool ShipField::attackShip(int x, int y) {
    if (x < 0 ||  y < 0 ) {
        return false;
    }
    size_t x_size = static_cast<size_t>(x);
    size_t y_size = static_cast<size_t>(y);
    if (x_size >= width || y_size >= height) {
        return false;
    }

    if (field[y_size][x_size].is_ship == false) {
        field[y_size][x_size].state = ShipField::CellVisibilityState::BLANK;
        return false;
    }
    Ship *current = field[y_size][x_size].ship;
    if (current->getSegment(field[y_size][x_size].ship_segment_index).hp <= 0) {
        return false;
    }
    field[y_size][x_size].state = ShipField::CellVisibilityState::SHIP;
    current->takeDamage(field[y_size][x_size].ship_segment_index, 1);
    return true;
}

size_t ShipField::getWidth() const {
    return width;
}

size_t ShipField::getHeight() const {
    return height;
}

void ShipField::clearField() {
    for (size_t i = 0; i < height; i++) {
        for (size_t j = 0; j < width; j++) {
            field[i][j] = FieldElement{ShipField::CellVisibilityState::UNKNOWN, nullptr, false, 0, 0};
        }
    }
}

ShipField::CellVisibilityState ShipField::getCellVisibilityState(int x, int y) const {
    if (x < 0 || y < 0) {
        return ShipField::CellVisibilityState::UNKNOWN;
    }
    if (static_cast<size_t>(x) >= width || static_cast<size_t>(y) >= height) {
        return ShipField::CellVisibilityState::UNKNOWN;
    }
    return field[y][x].state;
}


size_t ShipField::getShipIndex(int x, int y) const {
    if (x < 0 || y < 0) {
        return 0;
    }
    if (static_cast<size_t>(x) >= width || static_cast<size_t>(y) >= height) {
        return 0;
    }
    return field[y][x].ship_index;
}

size_t ShipField::getShipSegmentIndex(int x, int y) const {
    if (x < 0 || y < 0) {
        return 0;
    }
    if (static_cast<size_t>(x) >= width || static_cast<size_t>(y) >= height) {
        return 0;
    }
    return field[y][x].ship_segment_index;
}


int ShipField::getShipSegmentHP(int x, int y) const {
    if (x < 0 || y < 0) {
        return 0;
    }
    if (static_cast<size_t>(x) >= width || static_cast<size_t>(y) >= height) {
        return 0;
    }
    if (field[y][x].is_ship == false) {
        return 0;
    }
    return field[y][x].ship->getSegment(field[y][x].ship_segment_index).hp;
}


Ship::SegmentState ShipField::getShipSegmentState(int x, int y) const {
    if (x < 0 || y < 0) {
        return Ship::SegmentState::DESTROYED;
    }
    if (static_cast<size_t>(x) >= width || static_cast<size_t>(y) >= height) {
        return Ship::SegmentState::DESTROYED;
    }
    if (field[y][x].is_ship == false) {
        return Ship::SegmentState::DESTROYED;
    }
    return field[y][x].ship->getSegment(field[y][x].ship_segment_index).state;
}