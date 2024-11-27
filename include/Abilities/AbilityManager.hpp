#ifndef ABILITYMANAGER_HPP
#define ABILITYMANAGER_HPP

#include <functional>
#include <istream>
#include <memory>
#include <ostream>
#include <queue>

#include "Abilities/Ability.hpp"
#include "Abilities/AbilityResults.hpp"
class AbilityManager {
    std::queue<std::shared_ptr<Ability>> abilities;
    const std::vector<std::function<std::shared_ptr<Ability>()>> ability_factory;
    std::shared_ptr<Ability> getRandomAbility();

   public:
    AbilityManager();
    void useAbility(AbilityInput input, AbilityResults& ability_results);

    void addRandomAbility();
    AbilityType getPendingAbilityType() const;
    // bool empty() const;

    friend std::ostream& operator<<(std::ostream& os, const AbilityManager& manager);
    friend std::istream& operator>>(std::istream& is, AbilityManager& manager);
};

#endif  // ABILITYMANAGER_HPP