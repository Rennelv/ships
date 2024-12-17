#include "GameController.hpp"
#include "GameGui.hpp"
#include "Enums.hpp"
#include "Game.hpp"
#include "GameRenderer.hpp"
#include "TerminalInput.hpp"

int main() {
    // Game game;
    // GameGui gui(game);
    // gui.run();


    Game game;

    TerminalInput input;
    GameController<TerminalInput> controller(game, input);

    GameGui gui(game);
    GameRenderer<GameGui> renderer(gui);
    
    game.nextStage();
    while (game.getCurrentStage() != Stage::EXIT) {
        renderer.render();
        controller.processInput();
    }
    return 0;
}