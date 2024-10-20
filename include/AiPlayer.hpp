#ifndef AIPLAYER_HPP
#define AIPLAYER_HPP

#include <random>

#include "Abilities/AbilityManager.hpp"
#include "Player.hpp"
#include "ShipField.hpp"
#include "ShipManager.hpp"
class AiPlayer : public Player {
    ShipManager* shipManager = nullptr;
    ShipField* field = nullptr;
    AbilityManager* abilityManager = nullptr;
    AbilityResults abilityResults;
    // randomness
    std::random_device rd;
    std::mt19937 gen;
    std::uniform_int_distribution<int> disX;
    std::uniform_int_distribution<int> disY;

   public:
    AiPlayer();
    ~AiPlayer();
    void createField(int width, int height);
    // void createShipManager(size_t count, size_t* lengths);
    // void attackShip(int x, int y, bool exposeCell, int damage);
    // void useAbility(int x, int y) = delete;
    // void placeShip(Ship& ship, int x, int y, ShipOrientation orientation);
    // void placeShipByIndex(int index, int x, int y, ShipOrientation orientation);

    // size_t getShipCount() const;
    // size_t getShipLength(size_t index) const;
    // size_t getAliveCount() const;
    // AbilityType getPendingAbilityType() const = delete;

    // AbilityResults& getAbilityResults() = delete;

    // const ShipField& getField() const;
    // const ShipManager& getShipManager() const;
    // const AbilityManager& getAbilityManager() const;

    void attackRandomCell(Player& otherPlayer);
    void placeShipsRandomly();
};

#endif  // PLAYER_HPP