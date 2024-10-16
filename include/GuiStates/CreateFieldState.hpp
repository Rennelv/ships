#ifndef CREATEFIELDSTATE_HPP
#define CREATEFIELDSTATE_HPP

#include <SFML/Graphics.hpp>
#include <SFML/Window/Event.hpp>
#include <memory>

#include "GuiStates/State.hpp"
#include "ShipField.hpp"

class CreateFieldState : public State {
    GameState nextState = GameState::CreateField;
    std::unique_ptr<ShipField> &field;
    int fieldWidth = 10;
    int fieldHeight = 10;
    sf::Font font;
    sf::Text fieldSizeText;
    void drawField(sf::RenderWindow &window);

   public:
    CreateFieldState(std::unique_ptr<ShipField> &field);
    void handleInput(sf::Event &event) override;
    void update() override;
    void render(sf::RenderWindow &window) override;
    GameState changeState() override;
};

#endif  // CREATEFIELDSTATE_HPP