#ifndef ABILITYMANAGER_HPP
#define ABILITYMANAGER_HPP

#include <memory>
#include <queue>

#include "Abilities/Ability.hpp"
#include "Abilities/AbilityResults.hpp"
#include "ShipField.hpp"

class AbilityManager {
   private:
    std::queue<std::unique_ptr<Ability>> abilities;
    std::unique_ptr<Ability> getRandomAbility();

   public:
    AbilityManager();
    void useAbility(ShipField& field, ShipManager& manager, int x, int y, AbilityResults& ability_results);

    void addRandomAbility();
    AbilityType getPendingAbilityType() const;
    bool empty() const;
};

#endif  // ABILITYMANAGER_HPP