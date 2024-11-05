#include "Player.hpp"

#include "Abilities/AbilityManager.hpp"
#include "ShipManager.hpp"

Player::Player() : shipManager(), field(10, 10), abilityManager() {
}

void Player::createField(int width, int height) {
    // delete field;
    field = ShipField(width, height);
}

void Player::createShipManager(size_t count, size_t* lengths) {
    // delete shipManager;
    shipManager = ShipManager(count, lengths);
}

void Player::attackShip(int x, int y, bool exposeCell, int damage) {
    bool was_killed = field.attackShip(x, y, exposeCell, damage);
    if (was_killed) abilityManager.addRandomAbility();
}

// void Player::useAbility(int x, int y) {
//     abilityManager.useAbility(field, shipManager, x, y, abilityResults);
// }

void Player::placeShip(Ship& ship, int x, int y, ShipOrientation orientation) {
    field.placeShip(ship, x, y, orientation);
}

void Player::placeShipByIndex(int index, int x, int y, ShipOrientation orientation) {
    Ship& ship = shipManager.getShip(index);
    placeShip(ship, x, y, orientation);
}

size_t Player::getShipCount() const {
    return shipManager.getShipCount();
}

size_t Player::getShipLength(size_t index) const {
    return shipManager.getShipLength(index);
}

size_t Player::getAliveCount() const {
    return shipManager.getAliveCount();
}

AbilityResults& Player::getAbilityResults() {
    return abilityResults;
}

AbilityType Player::getPendingAbilityType() const {
    return abilityManager.getPendingAbilityType();
}

const ShipField& Player::getField() const {
    return field;
}

// const ShipManager& Player::getShipManager() const {
//     return *shipManager;
// }

// const AbilityManager& Player::getAbilityManager() const {
//     return *abilityManager;
// }

void Player::attack(Player& targetPlayer, int x, int y, int damage, bool exposeCell) {
    bool was_killed = targetPlayer.field.attackShip(x, y, exposeCell, damage);
    if (was_killed) abilityManager.addRandomAbility();
}

void Player::useAbility(Player& targetPlayer, int x, int y) {
    abilityManager.useAbility(targetPlayer.field, targetPlayer.shipManager, x, y, abilityResults);
}