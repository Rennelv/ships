#ifndef CREATEFIELDSTATE_HPP
#define CREATEFIELDSTATE_HPP

#include <SFML/Graphics.hpp>
#include <SFML/Window/Event.hpp>

#include "ShipField.hpp"
#include "state.hpp"

class CreateFieldState : public State {
    GameState nextState = GameState::CreateField;
    ShipField *&field;
    int fieldWidth = 10;
    int fieldHeight = 10;
    sf::Font font;
    sf::Text fieldSizeText;
    sf::RectangleShape fieldRepresentation;

   public:
    CreateFieldState(ShipField *&field);
    void handleInput(sf::Event &event) override;
    void update() override;
    void render(sf::RenderWindow &window) override;
    GameState changeState() override;
};

#endif  // CREATEFIELDSTATE_HPP