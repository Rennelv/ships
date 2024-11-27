#ifndef PAUSEATTACKINGSHIPSTATE_HPP
#define PAUSEATTACKINGSHIPSTATE_HPP

#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Window/Event.hpp>

#include "GameGui.hpp"
#include "GuiStates/State.hpp"

class SaveLoadState : public State {
    GameState next_state = GameState::SaveLoadState;

    GameGui& game;

    sf::Font font;
    sf::Text instruction_text;
    sf::Text result_text;

    void loadGameHelper();
    void saveGameHelper();

   public:
    SaveLoadState(GameGui& game_gui);
    void handleInput(sf::Event& event) override;
    void update() override;
    void render(sf::RenderWindow& window) override;
    GameState changeState() override;
};

#endif  // PAUSEATTACKINGSHIPSTATE_HPP