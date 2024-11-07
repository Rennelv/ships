#ifndef MENUSTATE_HPP
#define MENUSTATE_HPP

#include <SFML/Graphics.hpp>
#include <SFML/Window/Event.hpp>
#include <vector>

#include "GuiStates/State.hpp"

class MenuState : public State {
    GameState next_state = GameState::Menu;

    std::vector<sf::Text> menu_items;
    size_t selected_item_index;
    sf::Font font;

    void moveUp();
    void moveDown();
    void selectItem();

   public:
    MenuState();
    void handleInput(sf::Event &event) override;
    void update() override;
    void render(sf::RenderWindow &window) override;
    GameState changeState() override;
};

#endif  // MENUSTATE_HPP