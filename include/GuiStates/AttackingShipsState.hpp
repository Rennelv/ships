#ifndef ATTACKINGSHIPSTATE_HPP
#define ATTACKINGSHIPSTATE_HPP

#include <SFML/Graphics.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Window/Event.hpp>

#include "AiPlayer.hpp"
#include "GuiStates/State.hpp"
#include "Player.hpp"

class AttackingShipsState : public State {
    GameState next_state = GameState::AttackingShips;

    size_t current_x;
    size_t current_y;

    Player &player;
    AiPlayer &ai_player;

    sf::Font font;
    sf::Text instruction_text;
    sf::Text result_text;
    sf::RectangleShape selection_box;
    sf::Vector2f draw_offset;
    sf::Vector2f draw_offset2;
    sf::Vector2f cell_size;

    void drawField(sf::RenderWindow &window, Player &player, sf::Vector2f draw_offset, bool show_ships = false);
    void onAbilityUse();
    void onAttackUse();

   public:
    AttackingShipsState(Player &player, AiPlayer &player2);
    void handleInput(sf::Event &event) override;
    void update() override;
    void render(sf::RenderWindow &window) override;
    GameState changeState() override;
};

#endif  // ATTACKINGSHIPSTATE_HPP