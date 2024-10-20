#ifndef CREATESHIPSTATE_HPP
#define CREATESHIPSTATE_HPP

#include <SFML/Graphics/Text.hpp>

#include "AiPlayer.hpp"
#include "GuiStates/State.hpp"
#include "Player.hpp"

struct InputBox {
    sf::RectangleShape box;
    int value;
};

class CreateShipState : public State {
   public:
    CreateShipState(Player& player, AiPlayer& aiPlayer);
    void handleInput(sf::Event& event) override;
    void update() override;
    void render(sf::RenderWindow& window) override;
    GameState changeState() override;

   private:
    void createShips();
    Player& player;
    AiPlayer& aiPlayer;
    InputBox inputBoxes[4];
    int activeBoxIndex;
    GameState nextState = GameState::CreateShips;
    sf::Text titleText;
    sf::Text shipsText;
    sf::Text numberShipsText;
    sf::Font font;
    sf::Vector2f drawOffset;
};

#endif  // CREATESHIPSTATE_HPP