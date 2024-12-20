#ifndef PLACINGSHIPSTATE_HPP
#define PLACINGSHIPSTATE_HPP

#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Window/Event.hpp>

#include "Game.hpp"
#include "GuiStates/State.hpp"

class PlacingShipsState : public RendererState {
    // size_t current_x;
    // size_t current_y;
    // size_t current_ship_index;
    // ShipOrientation orientation = ShipOrientation::VERTICAL;

    const Game& game;

    sf::Font font;
    sf::Text instruction_text;
    sf::Text result_text;
    sf::RectangleShape ship_representation;
    sf::Vector2f draw_offset;
    sf::Vector2f cell_size;

    void drawField(sf::RenderWindow& window);
    // void placeShipHelper();

    bool err;


   public:
    PlacingShipsState(const Game& game);
    void update() override;
    void render(sf::RenderWindow& window) override;
    void printErr(std::string msg) override;
};

#endif  // PLACINGSHIPSTATE_HPP