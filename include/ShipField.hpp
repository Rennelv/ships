#ifndef SHIPFIELD_HPP
#define SHIPFIELD_HPP

#include <cstddef>

#include "Enums.hpp"
#include "Ship.hpp"

class ShipField {
    struct FieldElement {
        CellVisibilityState state = CellVisibilityState::UNKNOWN;
        Ship* ship = nullptr;
        size_t ship_segment_index = 0;
    };
    size_t width;
    size_t height;
    FieldElement** field;
    void exposeSurroundingShipCells(int ship_length, int x, int y);  // exposes cells around ship

   public:
    ShipField();
    ShipField(int width, int height);
    ~ShipField();

    ShipField(const ShipField& other);                 // Copy constructor
    ShipField(ShipField&& other) noexcept;             // Move constructor
    ShipField& operator=(const ShipField& other);      // Copy assignment operator
    ShipField& operator=(ShipField&& other) noexcept;  // Move assignment operator

    size_t getWidth() const;                                                                    // returns width of field
    size_t getHeight() const;                                                                   // returns height of field
    bool checkShipCollision(int ship_length, int x, int y, ShipOrientation orientation) const;  // returns true if ship collides with another ship
    CellVisibilityState getCellVisibilityState(int x, int y) const;                             // returns state of cell
    bool getIsShip(int x, int y) const;                                                         // returns true if cell contains ship
    // int getShipSegmentHP(int x, int y) const;                               // returns hp of segment in ship
    ShipSegmentState getShipSegmentState(int x, int y) const;                // returns state of segment in ship
    void placeShip(Ship& ship, int x, int y, ShipOrientation orientation);   // places ship on field
    bool attackShip(int x, int y, bool expose_cell = true, int damage = 1);  // attacks ship on field
    void clearField();                                                       // clears field
};

#endif  // SHIPFIELD_HPP