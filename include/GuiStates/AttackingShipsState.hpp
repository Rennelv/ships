#ifndef ATTACKINGSHIPSTATE_HPP
#define ATTACKINGSHIPSTATE_HPP

#include <SFML/Graphics.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Window/Event.hpp>

#include "GuiStates/State.hpp"
#include "Player.hpp"

class AttackingShipsState : public RendererState {
    size_t current_x;
    size_t current_y;

    const Player &player;
    const Player &player2;

    sf::Font font;
    sf::Text instruction_text;
    sf::Text result_text;
    sf::RectangleShape selection_box;
    sf::Vector2f draw_offset;
    sf::Vector2f draw_offset2;
    sf::Vector2f cell_size;

    void drawField(sf::RenderWindow &window, const Player &player, sf::Vector2f draw_offset, bool show_ships = false);
    // void onAbilityUse();
    // void onAttackUse();

   public:
    AttackingShipsState(const Player &player, const Player &player2);
    void update() override;
    void render(sf::RenderWindow &window) override;
};

#endif  // ATTACKINGSHIPSTATE_HPP