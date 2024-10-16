#ifndef MENUSTATE_HPP
#define MENUSTATE_HPP

#include <SFML/Graphics.hpp>
#include <SFML/Window/Event.hpp>
#include <vector>

#include "GuiStates/State.hpp"

class MenuState : public State {
   public:
    MenuState();
    void handleInput(sf::Event &event) override;
    void update() override;
    void render(sf::RenderWindow &window) override;
    GameState changeState() override;

   private:
    std::vector<sf::Text> menuItems;
    size_t selectedItemIndex;
    sf::Font font;
    GameState nextState = GameState::Menu;

    void moveUp();
    void moveDown();
    void selectItem();
};

#endif  // MENUSTATE_HPP