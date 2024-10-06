#ifndef SHIPFIELD_HPP
#define SHIPFIELD_HPP

#include <cstddef>

#include "Ship.hpp"

class ShipField {
   public:
    enum CellVisibilityState { UNKNOWN, BLANK, SHIP };

   private:
    struct FieldElement {
        CellVisibilityState state;
        Ship* ship;
        bool is_ship;
        size_t ship_index;
        size_t ship_segment_index;
    };
    size_t width;
    size_t height;
    FieldElement** field;

   public:
    ShipField(int width, int height);
    ~ShipField();

    ShipField(const ShipField& other);                 // Copy constructor
    ShipField(ShipField&& other) noexcept;             // Move constructor
    ShipField& operator=(const ShipField& other);      // Copy assignment operator
    ShipField& operator=(ShipField&& other) noexcept;  // Move assignment operator

    size_t getWidth() const;
    size_t getHeight() const;
    // FieldElement getCell(int x, int y) const;
    // FieldElement& getCell(int x, int y) const;
    CellVisibilityState getCellVisibilityState(int x, int y) const;
    bool getIsShip(int x, int y) const;
    size_t getShipIndex(int x, int y) const;
    size_t getShipSegmentIndex(int x, int y) const;
    int getShipSegmentHP(int x, int y) const;
    Ship::SegmentState getShipSegmentState(int x, int y) const;
    bool placeShip(Ship* ship, int x, int y, Ship::Orientation orientation);
    bool attackShip(int x, int y);
    void clearField();
};

#endif  // SHIPFIELD_HPP