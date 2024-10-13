#ifndef STATE_HPP
#define STATE_HPP

#include <SFML/Graphics.hpp>
#include <SFML/Window/Event.hpp>

enum class GameState {
    Menu,
    CreateField,
    PlacingShips,
    AttackingShips,
    Exit,
};

class State {
   public:
    virtual ~State() = default;
    virtual void handleInput(sf::Event &event) = 0;
    virtual void update() = 0;
    virtual void render(sf::RenderWindow &window) = 0;
    virtual GameState changeState() = 0;
};

#endif  // STATE_HPP