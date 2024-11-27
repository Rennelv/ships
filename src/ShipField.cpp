// ShipField.cpp

#include "ShipField.hpp"

#include <cstddef>
#include <set>
#include <stdexcept>
#include <string>
#include <unordered_map>
#include <utility>

#include "Enums.hpp"
#include "Exceptions/Exceptions.hpp"
#include "Ship.hpp"
#include "ShipManager.hpp"

ShipField::ShipField() {
    width = 0;
    height = 0;
    field = nullptr;
}

ShipField::ShipField(int new_width, int new_height) {
    if (new_width <= 0 || new_height <= 0) {
        throw std::invalid_argument("Width and height must be greater than 0");
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
    width = other.width;
    height = other.height;
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
        width = other.width;
        height = other.height;
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
    width = other.width;
    height = other.height;
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
        width = other.width;
        height = other.height;
        field = other.field;
        other.field = nullptr;
        other.width = 0;
        other.height = 0;
    }
    return *this;
}

bool ShipField::checkShipCollision(int ship_length, int head_x, int head_y, ShipOrientation orientation) const {
    if (orientation == ShipOrientation::HORIZONTAL) {
        if (head_x + ship_length > static_cast<int>(width)) {
            return true;
        }
        for (int x = head_x - 1; x < head_x + ship_length + 1; x++) {
            for (int y = head_y - 1; y < head_y + 2; y++) {
                if (x < 0 || y < 0 || x >= static_cast<int>(width) || y >= static_cast<int>(height)) {
                    continue;
                }
                if (getIsShip(x, y)) {
                    return true;  // cant place ship
                }
            }
        }
    } else {
        if (head_y + ship_length > static_cast<int>(height)) {
            return true;
        }
        for (int x = head_x - 1; x < head_x + 2; x++) {
            for (int y = head_y - 1; y < head_y + ship_length + 1; y++) {
                if (x < 0 || y < 0 || x >= static_cast<int>(width) || y >= static_cast<int>(height)) {
                    continue;
                }
                if (getIsShip(x, y)) {
                    return true;  // cant place ship
                }
            }
        }
    }
    return false;
}

ShipOrientation ShipField::getShipOrientation(int x, int y) const {
    if (x < 0 || y < 0) {
        throw std::invalid_argument("Coordinates must be non-negative");
    }
    if (static_cast<size_t>(x) >= width || static_cast<size_t>(y) >= height) {
        throw std::invalid_argument("Coordinates are out of field bounds");
    }
    if (getIsShip(x, y) == false) {
        throw std::logic_error("No ship at the given coordinates");
    }
    if (getIsShip(x, y - 1) || getIsShip(x, y + 1)) {
        return ShipOrientation::VERTICAL;
    }
    return ShipOrientation::HORIZONTAL;
}

std::pair<int, int> ShipField::getShipHead(int x, int y) const {
    ShipOrientation orientation = getShipOrientation(x, y);
    if (orientation == ShipOrientation::HORIZONTAL) {
        while (getIsShip(x - 1, y)) {
            x--;
        }
    } else {
        while (getIsShip(x, y - 1)) {
            y--;
        }
    }
    return std::make_pair(x, y);
}

void ShipField::exposeSurroundingShipCells(int ship_length, int head_x, int head_y) {
    ShipOrientation orientation = getShipOrientation(head_x, head_y);

    auto ship_head = getShipHead(head_x, head_y);
    head_x = ship_head.first;
    head_y = ship_head.second;

    if (orientation == ShipOrientation::HORIZONTAL) {
        for (int x = head_x - 1; x < head_x + ship_length + 1; x++) {
            for (int y = head_y - 1; y < head_y + 2; y++) {
                if (x < 0 || y < 0 || x >= static_cast<int>(width) || y >= static_cast<int>(height)) {
                    continue;
                }
                if (getIsShip(x, y)) {
                    field[y][x].state = CellVisibilityState::SHIP;
                } else {
                    field[y][x].state = CellVisibilityState::BLANK;
                }
            }
        }
    } else {
        for (int x = head_x - 1; x < head_x + 2; x++) {
            for (int y = head_y - 1; y < head_y + ship_length + 1; y++) {
                if (x < 0 || y < 0 || x >= static_cast<int>(width) || y >= static_cast<int>(height)) {
                    continue;
                }
                if (getIsShip(x, y)) {
                    field[y][x].state = CellVisibilityState::SHIP;
                } else {
                    field[y][x].state = CellVisibilityState::BLANK;
                }
            }
        }
    }
}

void ShipField::placeShip(Ship &ship, int x, int y, ShipOrientation orientation) {
    const size_t ship_length = ship.getLength();

    if (x < 0 || y < 0) {  // 0 0 is the bottom left corner
        throw std::invalid_argument("Coordinates cant be negative");
    }

    const size_t x_size = static_cast<size_t>(x);
    const size_t y_size = static_cast<size_t>(y);

    if (y_size >= height || x_size >= width) {
        throw std::invalid_argument("Coordinates are out of field bounds");
    }

    if (checkShipCollision(ship_length, x_size, y_size, orientation)) {
        throw std::invalid_argument("Ship collides with another ship or borders");
    }

    if (orientation == ShipOrientation::HORIZONTAL) {  // horizontal placement of the ship on the field
        for (size_t i = x_size; i < x_size + ship_length; i++) {
            field[y_size][i].ship = &ship;
            field[y_size][i].ship_segment_index = i - x_size;
        }
    } else {  // vertical placement of the ship on the field
        for (size_t i = y_size; i < y_size + ship_length; i++) {
            field[i][x_size].ship = &ship;
            field[i][x_size].ship_segment_index = i - y_size;
        }
    }
}

bool ShipField::attackShip(int x, int y, bool expose_cell, int damage) {
    if (x < 0 || y < 0 || static_cast<size_t>(x) >= width || static_cast<size_t>(y) >= height) {
        throw exceptions::OutOfBoundsAttackException("Coordinates are out of field bounds");
    }

    if (getIsShip(x, y) == false) {
        if (expose_cell) field[y][x].state = CellVisibilityState::BLANK;
        return false;
    }

    Ship *current = field[y][x].ship;
    const size_t ship_segment_index = field[y][x].ship_segment_index;

    if (expose_cell) field[y][x].state = CellVisibilityState::SHIP;

    if (current->getSegmentHP(ship_segment_index) <= 0) {
        return false;
    }

    current->takeDamage(ship_segment_index, damage);
    if (current->isAlive() == false) {
        exposeSurroundingShipCells(current->getLength(), x, y);
        return true;
    }
    return false;
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
    return (!(field[y][x].ship == nullptr));
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

std::ostream &operator<<(std::ostream &os, const ShipField &field) {
    os << "===Field===\n";
    os << field.width << ' ' << field.height << '\n';
    std::unordered_map<Ship *, std::pair<int, int>> ship_heads;
    std::unordered_map<Ship *, int> ship_indexes;
    for (size_t i = 0; i < field.height; i++) {
        for (size_t j = 0; j < field.width; j++) {
            int head_x = static_cast<int>(j);
            int head_y = static_cast<int>(i);
            if (field.getIsShip(j, i)) {
                auto ship_head = field.getShipHead(head_x, head_y);
                head_x = ship_head.first;
                head_y = ship_head.second;

                ship_heads.emplace(field.field[i][j].ship, field.getShipHead(head_x, head_y));
            }
            os << static_cast<int>(field.field[i][j].state) << ' ';
        }
        os << '\n';
    }
    os << "===End Field===\n";

    os << "===Field Ships===\n";
    os << ship_heads.size() << '\n';
    for (auto ship_head : ship_heads) {
        auto ship = ship_head.first;
        auto head = ship_head.second;
        ShipOrientation orientation = field.getShipOrientation(head.first, head.second);
        os << static_cast<int>(ship->getLength()) << ' ' << head.first << ' ' << head.second << ' ' << static_cast<int>(orientation) << '\n';
        os << *ship;
    }
    os << "===End Field Ships===\n";
    return os;
}

std::istream &operator>>(std::istream &is, ShipField &field) {
    std::string line;
    is >> std::ws;
    std::getline(is, line);
    if (line != "===Field===") {
        throw std::invalid_argument("Invalid save file");
    }
    size_t width, height;
    is >> width >> height;
    field = ShipField(width, height);
    for (size_t i = 0; i < field.height; i++) {
        for (size_t j = 0; j < field.width; j++) {
            int state;
            is >> state;
            field.field[i][j].state = static_cast<CellVisibilityState>(state);
        }
    }
    is >> std::ws;
    std::getline(is, line);
    if (line != "===End Field===") {
        throw std::invalid_argument("Invalid save file");
    }

    return is;
}

void ShipField::restoreShips(std::istream &is, ShipManager &manager) {
    std::string line;
    is >> std::ws;
    std::getline(is, line);
    if (line != "===Field Ships===") {
        throw std::invalid_argument("Invalid save file");
    }
    size_t ship_count;
    is >> ship_count;
    std::set<int> used_ship_indexes;
    for (size_t i = 0; i < ship_count; i++) {
        int length, x, y, orientation;
        is >> length >> x >> y >> orientation;
        ShipOrientation ship_orientation = static_cast<ShipOrientation>(orientation);
        Ship temp_ship(length);
        is >> temp_ship;

        for (size_t ship_index = 0; ship_index < manager.getShipCount(); ship_index++) {
            if (manager.getShip(ship_index) == temp_ship && used_ship_indexes.find(ship_index) == used_ship_indexes.end()) {
                used_ship_indexes.insert(ship_index);
                placeShip(manager.getShip(ship_index), x, y, ship_orientation);
                break;
            }
            if (ship_index == manager.getShipCount() - 1) {
                throw std::invalid_argument("Invalid save file");
            }
        }
    }
    is >> std::ws;
    std::getline(is, line);
    if (line != "===End Field Ships===") {
        throw std::invalid_argument("Invalid save file");
    }
}

bool ShipField::operator==(const ShipField &other) const {
    if (width != other.width || height != other.height) {
        return false;
    }
    for (size_t i = 0; i < height; i++) {
        for (size_t j = 0; j < width; j++) {
            if (field[i][j].state != other.field[i][j].state) {
                return false;
            }
            if (field[i][j].ship != nullptr && other.field[i][j].ship != nullptr) {
                if (*field[i][j].ship != *other.field[i][j].ship) {
                    return false;
                }
            } else if (field[i][j].ship != nullptr || other.field[i][j].ship != nullptr) {
                return false;
            }
        }
    }
    return true;
}

bool ShipField::operator!=(const ShipField &other) const {
    return !(*this == other);
}