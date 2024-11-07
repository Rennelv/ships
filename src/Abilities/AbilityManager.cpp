
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
#include "Exceptions/Exceptions.hpp"
#include "ShipField.hpp"
#include "ShipManager.hpp"

std::unique_ptr<Ability> AbilityManager::getRandomAbility() {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0, ability_factory.size() - 1);

    return ability_factory[dis(gen)]();
}

AbilityManager::AbilityManager()
    : ability_factory({
          []() { return std::make_unique<DoubleDamageAbility>(); },
          []() { return std::make_unique<ScannerAbility>(); },
          []() { return std::make_unique<BombardAbility>(); },
      }) {
    std::vector<std::unique_ptr<Ability>> temp_abilities;
    for (const auto &factory : ability_factory) {
        temp_abilities.push_back(factory());
    }

    std::random_device rd;
    std::mt19937 gen(rd());
    std::shuffle(temp_abilities.begin(), temp_abilities.end(), gen);

    for (auto &ability : temp_abilities) {
        abilities.push(std::move(ability));
    }
}

void AbilityManager::useAbility(ShipField &target_field, ShipManager &target_ship_manager, int x, int y, AbilityResults &ability_results) {
    if (abilities.empty()) {
        throw exceptions::NoAbilityAvailableException();
    }
    abilities.front()->use(target_field, target_ship_manager, x, y, ability_results);
    abilities.pop();
}

void AbilityManager::addRandomAbility() {
    abilities.push(getRandomAbility());
}

AbilityType AbilityManager::getPendingAbilityType() const {
    if (abilities.empty()) {
        throw exceptions::NoAbilityAvailableException();
    }
    return abilities.front()->getType();
}

// bool AbilityManager::empty() const {
//     return abilities.empty();
// }
