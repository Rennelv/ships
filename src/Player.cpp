#include "Player.hpp"

#include "Abilities/AbilityManager.hpp"
#include "ShipManager.hpp"

Player::Player() : ship_manager(), field(10, 10), ability_manager() {
}

void Player::createField(int width, int height) {
    field = ShipField(width, height);
}

void Player::createShipManager(size_t count, size_t* lengths) {
    ship_manager = ShipManager(count, lengths);
}

void Player::placeShip(Ship& ship, int x, int y, ShipOrientation orientation) {
    field.placeShip(ship, x, y, orientation);
}

void Player::placeShipByIndex(int index, int x, int y, ShipOrientation orientation) {
    Ship& ship = ship_manager.getShip(index);
    placeShip(ship, x, y, orientation);
}

size_t Player::getShipCount() const {
    return ship_manager.getShipCount();
}

size_t Player::getShipLength(size_t index) const {
    return ship_manager.getShipLength(index);
}

size_t Player::getAliveCount() const {
    return ship_manager.getAliveCount();
}

AbilityResults Player::getAbilityResults() {
    return ability_results;
}

AbilityType Player::getPendingAbilityType() const {
    return ability_manager.getPendingAbilityType();
}

const ShipField& Player::getField() const {
    return field;
}

void Player::attack(Player& targetPlayer, int x, int y, int damage, bool exposeCell) {
    if (ability_results.DoubleDamageIsActive) {
        damage *= 2;
        ability_results.DoubleDamageIsActive = false;
    }
    bool was_killed = targetPlayer.field.attackShip(x, y, exposeCell, damage);
    if (was_killed) ability_manager.addRandomAbility();
}

void Player::useAbility(Player& targetPlayer, int x, int y) {
    ability_manager.useAbility(targetPlayer.field, targetPlayer.ship_manager, x, y, ability_results);
}