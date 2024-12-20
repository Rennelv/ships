#include "Enums.hpp"
#include "Game.hpp"
#include "GameController.hpp"
#include "GameGui.hpp"
#include "GameRenderer.hpp"
#include "Input.hpp"

int main() {
    Game game;

    GameController<StreamInput> controller(game);

    GameRenderer<Gui> renderer(game);

    game.nextStage();
    renderer.render();

    while (game.getCurrentStage() != Stage::EXIT) {
        try{
            controller.processInput();
        } catch (const std::exception& e) {
            renderer.printErr(e.what());
        }
        // controller.processInput();
        renderer.render();
    }

    return 0;
}