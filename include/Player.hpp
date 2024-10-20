#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <cstddef>

#include "Abilities/Ability.hpp"
#include "Abilities/AbilityManager.hpp"
#include "ShipField.hpp"
#include "ShipManager.hpp"
class Player {
    ShipManager* shipManager;
    ShipField* field;
    AbilityManager* abilityManager;
    AbilityResults abilityResults;

   public:
    Player();
    ~Player();
    void createField(int width, int height);
    void createShipManager(size_t count, size_t* lengths);
    void attackShip(int x, int y, bool exposeCell = true, int damage = 1);
    void useAbility(int x, int y);
    void placeShip(Ship& ship, int x, int y, ShipOrientation orientation);
    void placeShipByIndex(int index, int x, int y, ShipOrientation orientation);

    size_t getShipCount() const;
    size_t getShipLength(size_t index) const;
    size_t getAliveCount() const;
    AbilityType getPendingAbilityType() const;

    AbilityResults& getAbilityResults();

    const ShipField& getField() const;
    // const ShipManager& getShipManager() const;
    // const AbilityManager& getAbilityManager() const;
};

#endif  // PLAYER_HPP