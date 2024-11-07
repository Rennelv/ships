
#include "Abilities/AbilityManager.hpp"

#include <algorithm>
#include <cstdlib>
#include <memory>
#include <queue>
#include <random>
#include <stdexcept>

#include "Abilities/Ability.hpp"
#include "Abilities/BombardAbility.hpp"
#include "Abilities/DoubleDamageAbility.hpp"
#include "Abilities/ScannerAbility.hpp"
#include "Exceptions/NoAbilitiesException.hpp"
#include "ShipField.hpp"
#include "ShipManager.hpp"

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

    std::random_device rd;
    std::mt19937 gen(rd());
    std::shuffle(std::begin(ab), std::end(ab), gen);

    for (auto &ability : ab) {
        abilities.push(std::move(ability));
    }
}

void AbilityManager::useAbility(ShipField &target_field, ShipManager &target_ship_manager, int x, int y, AbilityResults &ability_results) {
    if (abilities.empty()) {
        throw exceptions::NoAbilitiesException();
    }
    abilities.front()->use(target_field, target_ship_manager, x, y, ability_results);
    abilities.pop();
}

void AbilityManager::addRandomAbility() {
    abilities.push(getRandomAbility());
}

AbilityType AbilityManager::getPendingAbilityType() const {
    if (abilities.empty()) {
        throw exceptions::NoAbilitiesException();
    }
    return abilities.front()->getType();
}

bool AbilityManager::empty() const {
    return abilities.empty();
}
