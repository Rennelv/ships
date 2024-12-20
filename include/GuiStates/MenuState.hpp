#ifndef MENUSTATE_HPP
#define MENUSTATE_HPP

#include <SFML/Graphics.hpp>
#include <SFML/Window/Event.hpp>
#include <vector>

#include "GuiStates/State.hpp"

class MenuState : public RendererState {
    std::vector<sf::Text> menu_items;
    size_t selected_item_index;
    sf::Font font;

    void moveUp();
    void moveDown();
    void selectItem();

   public:
    MenuState();
    void update() override;
    void render(sf::RenderWindow &window) override;
    void printErr(std::string msg) override;
};

#endif  // MENUSTATE_HPP