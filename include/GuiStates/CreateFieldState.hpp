#ifndef CREATEFIELDSTATE_HPP
#define CREATEFIELDSTATE_HPP

#include <SFML/Graphics.hpp>
#include <SFML/Window/Event.hpp>

#include "GuiStates/State.hpp"
#include "Player.hpp"

class CreateFieldState : public State {
    GameState nextState = GameState::CreateField;
    Player &player;
    int fieldWidth = 10;
    int fieldHeight = 10;
    sf::Font font;
    sf::Text fieldSizeText;
    sf::Vector2f drawOffset;
    sf::Vector2f cellSize;
    void drawField(sf::RenderWindow &window);

   public:
    CreateFieldState(Player &player);
    void handleInput(sf::Event &event) override;
    void update() override;
    void render(sf::RenderWindow &window) override;
    GameState changeState() override;
};

#endif  // CREATEFIELDSTATE_HPP