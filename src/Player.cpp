#include "Player.hpp"

Player::Player() {
    size_t lengths[] = {4, 3, 2, 2, 1, 1};
    shipManager = new ShipManager(6, lengths);
    abilityManager = new AbilityManager();
    field = new ShipField(10, 10);
}

Player::~Player() {
    delete shipManager;
    delete field;
    delete abilityManager;
}

void Player::createField(int width, int height) {
    delete field;
    field = new ShipField(width, height);
}

void Player::createShipManager(size_t count, size_t* lengths) {
    delete shipManager;
    shipManager = new ShipManager(count, lengths);
}

void Player::attackShip(int x, int y, bool exposeCell, int damage) {
    bool was_killed = field->attackShip(x, y, exposeCell, damage);
    if (was_killed) abilityManager->addRandomAbility();
}

void Player::useAbility(int x, int y) {
    abilityManager->useAbility(*field, x, y, abilityResults);
}

void Player::placeShip(Ship& ship, int x, int y, ShipOrientation orientation) {
    field->placeShip(ship, x, y, orientation);
}

void Player::placeShipByIndex(int index, int x, int y, ShipOrientation orientation) {
    Ship& ship = shipManager->getShip(index);
    placeShip(ship, x, y, orientation);
}

const ShipField& Player::getField() const {
    return *field;
}

ShipManager& Player::getShipManager() const {
    return *shipManager;
}

const AbilityManager& Player::getAbilityManager() const {
    return *abilityManager;
}

AbilityResults& Player::getAbilityStatus() {
    return abilityResults;
}