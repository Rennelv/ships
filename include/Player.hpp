#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <cstddef>

#include "Abilities/AbilityManager.hpp"
#include "Abilities/AbilityType.hpp"
#include "ShipField.hpp"
#include "ShipManager.hpp"

class Player {
    ShipManager ship_manager;
    ShipField field;
    AbilityManager ability_manager;
    AbilityResults ability_results;

   public:
    bool scanner_is_active = false;

    Player();

    void createField(int width, int height);
    void createShipManager(size_t count, size_t* lengths);
    void placeShip(Ship& ship, int x, int y, ShipOrientation orientation);
    void placeShipByIndex(int index, int x, int y, ShipOrientation orientation);

    void attack(Player& target_player, int x, int y, int damage, bool expose_cell = true);
    void useAbility(Player& target_player, int x, int y);

    size_t getShipCount() const;
    size_t getShipLength(size_t index) const;
    size_t getAliveCount() const;
    AbilityType getPendingAbilityType() const;

    AbilityResults getAbilityResults();

    const ShipField& getField() const;
};

#endif  // PLAYER_HPP