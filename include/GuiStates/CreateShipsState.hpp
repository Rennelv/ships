#ifndef CREATESHIPSTATE_HPP
#define CREATESHIPSTATE_HPP

#include <SFML/Graphics/Text.hpp>

#include "Game.hpp"
#include "GuiStates/State.hpp"

struct InputBox {
    sf::RectangleShape box;
    int value;
};

class CreateShipState : public RendererState {
    const Game& game;

    InputBox input_boxes[4];
    int active_box_index;

    sf::Text title_text;
    sf::Text ships_text;
    sf::Text number_ships_text;
    sf::Font font;
    sf::Vector2f draw_offset;

    // void createShips();

    bool err;


   public:
    CreateShipState(const Game& game);
    void update() override;
    void render(sf::RenderWindow& window) override;
    void printErr(std::string msg) override;
};

#endif  // CREATESHIPSTATE_HPP