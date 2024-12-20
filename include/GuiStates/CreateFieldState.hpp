#ifndef CREATEFIELDSTATE_HPP
#define CREATEFIELDSTATE_HPP

#include <SFML/Graphics.hpp>
#include <SFML/Window/Event.hpp>

#include "Game.hpp"
#include "GuiStates/State.hpp"

class CreateFieldState : public RendererState {
    const Game& game;

    int field_width;
    int field_height;

    sf::Font font;
    sf::Text field_size_text;
    sf::Vector2f draw_offset;
    sf::Vector2f cell_size;

    void drawField(sf::RenderWindow& window);

    bool err;


   public:
    CreateFieldState(const Game& game);
    void update() override;
    void render(sf::RenderWindow& window) override;
    void printErr(std::string msg) override;
};

#endif  // CREATEFIELDSTATE_HPP