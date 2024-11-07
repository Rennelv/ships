#ifndef CREATEFIELDSTATE_HPP
#define CREATEFIELDSTATE_HPP

#include <SFML/Graphics.hpp>
#include <SFML/Window/Event.hpp>

#include "GuiStates/State.hpp"
#include "Player.hpp"

class CreateFieldState : public State {
    GameState next_state = GameState::CreateField;

    Player &player;

    int field_width;
    int field_height;

    sf::Font font;
    sf::Text field_size_text;
    sf::Vector2f draw_offset;
    sf::Vector2f cell_size;

    void drawField(sf::RenderWindow &window);

   public:
    CreateFieldState(Player &player);
    void handleInput(sf::Event &event) override;
    void update() override;
    void render(sf::RenderWindow &window) override;
    GameState changeState() override;
};

#endif  // CREATEFIELDSTATE_HPP