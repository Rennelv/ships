
#include "Abilities/AbilityManager.hpp"

#include <algorithm>
#include <cstdlib>
#include <memory>
#include <queue>
#include <random>

#include "Abilities/Ability.hpp"
#include "Abilities/BombardAbility.hpp"
#include "Abilities/DoubleDamageAbility.hpp"
#include "Abilities/ScannerAbility.hpp"
#include "Exceptions.hpp"
#include "ShipField.hpp"

std::unique_ptr<Ability> AbilityManager::getRandomAbility() {
    int random = rand() % 3;
    switch (random) {
        case 0:
            return std::make_unique<DoubleDamageAbility>();
        case 1:
            return std::make_unique<ScannerAbility>();
        case 2:
            return std::make_unique<BombardAbility>();
    }
    throw std::runtime_error("Invalid random number");
}

AbilityManager::AbilityManager() {
    std::unique_ptr<Ability> ab[] = {std::make_unique<DoubleDamageAbility>(), std::make_unique<ScannerAbility>(), std::make_unique<BombardAbility>()};

    // Obtain a random number from hardware
    std::random_device rd;
    // Seed the generator
    std::mt19937 gen(rd());
    // Shuffle the array
    std::shuffle(std::begin(ab), std::end(ab), gen);

    for (auto &ability : ab) {
        abilities.push(std::move(ability));
    }
}

void AbilityManager::useAbility(ShipField &field, int x, int y) {
    if (abilities.empty()) {
        throw NoAbilitiesException();
    }
    if (abilities.front()->getType() == AbilityType::Scanner) {
        if (!abilityResults.scannerIsActive) {
            abilityResults.scannerIsActive = true;
            return;
        } else {
            abilityResults.scannerIsActive = false;
        }
    }
    abilities.front()->use(field, x, y, abilityResults);
    abilities.pop();
}

void AbilityManager::addRandomAbility() {
    abilities.push(getRandomAbility());
}

AbilityType AbilityManager::getAbilityType() {
    if (abilities.empty()) {
        throw NoAbilitiesException();
    }
    return abilities.front()->getType();
}

AbilityResults &AbilityManager::getAbilityStatus() {
    return abilityResults;
}