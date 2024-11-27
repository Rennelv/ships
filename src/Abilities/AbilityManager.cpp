
#include "Abilities/AbilityManager.hpp"

#include <algorithm>
#include <cstdlib>
#include <memory>
#include <queue>
#include <random>

#include "Abilities/Ability.hpp"
#include "Abilities/AbilityResults.hpp"
#include "Abilities/BombardAbility.hpp"
#include "Abilities/DoubleDamageAbility.hpp"
#include "Abilities/ScannerAbility.hpp"
#include "Exceptions/Exceptions.hpp"

std::shared_ptr<Ability> AbilityManager::getRandomAbility() {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0, ability_factory.size() - 1);

    return ability_factory[dis(gen)]();
}

AbilityManager::AbilityManager()
    : ability_factory({
          []() { return std::make_shared<DoubleDamageAbility>(); },
          []() { return std::make_shared<ScannerAbility>(); },
          []() { return std::make_shared<BombardAbility>(); },
      }) {
    std::vector<std::shared_ptr<Ability>> temp_abilities;
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

void AbilityManager::useAbility(AbilityInput input, AbilityResults &ability_results) {
    if (abilities.empty()) {
        throw exceptions::NoAbilityAvailableException();
    }
    abilities.front()->use(input, ability_results);
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

std::ostream &operator<<(std::ostream &os, const AbilityManager &manager) {
    std::queue<std::shared_ptr<Ability>> temp_abilities = manager.abilities;
    os << "===Abilities===\n";
    os << manager.abilities.size() << '\n';
    while (!temp_abilities.empty()) {
        os << static_cast<int>(temp_abilities.front()->getType()) << ' ';
        temp_abilities.pop();
    }
    os << '\n';

    os << "===End Abilities===\n";
    return os;
}

std::istream &operator>>(std::istream &is, AbilityManager &manager) {
    std::string line;
    is >> std::ws;
    std::getline(is, line);
    if (line != "===Abilities===") {
        throw std::invalid_argument("Invalid save file");
    }
    int size;
    is >> size;
    while (!manager.abilities.empty()) {
        manager.abilities.pop();
    }
    // std::vector<int> ability_types;
    // ability_types.reserve(size);
    for (int i = 0; i < size; i++) {
        int type = -1;
        is >> type;
        if (type < 0 || static_cast<size_t>(type) > manager.ability_factory.size()) {
            throw std::invalid_argument("Invalid save file");
        }
        manager.abilities.push(manager.ability_factory[type]());
        // ability_types.push_back(type);
    }

    // std::reverse(ability_types.begin(), ability_types.end());

    // for (int type : ability_types) {
    // }

    is >> std::ws;
    std::getline(is, line);
    if (line != "===End Abilities===") {
        throw std::invalid_argument("Invalid save file");
    }

    return is;
}