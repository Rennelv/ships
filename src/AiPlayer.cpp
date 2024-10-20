#include "AiPlayer.hpp"

#include <stdexcept>

AiPlayer::AiPlayer() {
    size_t lengths[] = {4, 3, 2, 2, 1, 1};
    shipManager = new ShipManager(6, lengths);
    abilityManager = new AbilityManager();
    field = new ShipField(10, 10);
    // randomness
    gen = std::mt19937(rd());
    disX = std::uniform_int_distribution<int>(0, field->getWidth() - 1);
    disY = std::uniform_int_distribution<int>(0, field->getHeight() - 1);
}

AiPlayer::~AiPlayer() {
    delete shipManager;
    delete field;
    delete abilityManager;
}

void AiPlayer::createField(int width, int height) {
    delete field;
    field = new ShipField(width, height);
    disX = std::uniform_int_distribution<int>(0, field->getWidth() - 1);
    disY = std::uniform_int_distribution<int>(0, field->getHeight() - 1);
}

// void AiPlayer::createShipManager(size_t count, size_t* lengths) {
//     delete shipManager;
//     shipManager = new ShipManager(count, lengths);
// }

// void AiPlayer::attackShip(int x, int y, bool exposeCell, int damage) {
//     bool was_killed = field->attackShip(x, y, exposeCell, damage);
//     if (was_killed) abilityManager->addRandomAbility();
// }

// void AiPlayer::placeShip(Ship& ship, int x, int y, ShipOrientation orientation) {
//     field->placeShip(ship, x, y, orientation);
// }

// void AiPlayer::placeShipByIndex(int index, int x, int y, ShipOrientation orientation) {
//     Ship& ship = shipManager->getShip(index);
//     placeShip(ship, x, y, orientation);
// }

// size_t AiPlayer::getShipCount() const {
//     return shipManager->getShipCount();
// }

// size_t AiPlayer::getShipLength(size_t index) const {
//     return shipManager->getShip(index).getLength();
// }

// size_t AiPlayer::getAliveCount() const {
//     return shipManager->getAliveCount();
// }

// const ShipField& AiPlayer::getField() const {
//     return *field;
// }

void AiPlayer::attackRandomCell(Player& otherPlayer) {
    int x = disX(gen);
    int y = disY(gen);
    while (field->getCellVisibilityState(x, y) == CellVisibilityState::BLANK ||
           (field->getCellVisibilityState(x, y) == CellVisibilityState::SHIP && field->getShipSegmentState(x, y) == ShipSegmentState::DESTROYED)) {
        x = disX(gen);
        y = disY(gen);
    }
    otherPlayer.attackShip(x, y, true, 1);
}

void AiPlayer::placeShipsRandomly() {
    int badCount = 0;
    for (size_t i = 0; i < shipManager->getShipCount(); i++) {
        ShipOrientation orientation = static_cast<ShipOrientation>(disX(gen) % 2);
        int x = disX(gen);
        int y = disY(gen);
        try {
            placeShipByIndex(i, x, y, orientation);
        } catch (std::invalid_argument& e) {
            badCount++;
            if (badCount > 1000) {
                field->clearField();
                i = 0;
                badCount = 0;
                continue;
            }
            i--;
        }
    }
}