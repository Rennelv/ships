#ifndef PLACINGSHIPSTATE_HPP
#define PLACINGSHIPSTATE_HPP

#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Window/Event.hpp>

#include "GuiStates/State.hpp"
#include "Player.hpp"

class PlacingShipsState : public RendererState {
    // size_t current_x;
    // size_t current_y;
    // size_t current_ship_index;
    // ShipOrientation orientation = ShipOrientation::VERTICAL;

    const Player& player;

    sf::Font font;
    sf::Text instruction_text;
    sf::Text result_text;
    sf::RectangleShape ship_representation;
    sf::Vector2f draw_offset;
    sf::Vector2f cell_size;

    void drawField(sf::RenderWindow& window);
    // void placeShipHelper();

   public:
    PlacingShipsState(const Player& player);
    void update() override;
    void render(sf::RenderWindow& window) override;
};

#endif  // PLACINGSHIPSTATE_HPP