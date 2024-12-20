#ifndef GAMECONTROLLER_HPP
#define GAMECONTROLLER_HPP

#include <cstddef>
#include <vector>

// #include "Abilities/AbilityType.hpp"
#include "Enums.hpp"
#include "Game.hpp"
#include "InputCommands.hpp"

template <typename InputHandler>
class GameController {
   public:
    GameController(Game& game) : game(game), input_handler() {
    }

    void processInput() {
        // std::unordered_map<Stage, std::string> state_to_string = {
        //     {Stage::NOT_STARTED, "Not started"},       {Stage::CREATING_FIELD, "Creating field"},
        //     {Stage::CREATING_SHIPS, "Creating ships"}, {Stage::PLACING_SHIPS, "Placing ships"},
        //     {Stage::PLAYER_TURN, "Player turn"},       {Stage::AI_TURN, "Ai turn"},
        //     {Stage::GAME_OVER, "Game over"},           {Stage::EXIT, "Exit"},

        // };
        // std::cout << "Game stage: " << static_cast<int>(game.getCurrentStage()) << std::endl;
        input_handler.processInput();
        const InputCommand& command = input_handler.getCommand();
        executeCommand(command);
        game.checkWin();
    }

   private:
    void executeCommand(const InputCommand& command) {
        switch (command.command) {
            case InputCommands::CreateField: {
                // try {
                game.createField(command.arguments[0], command.arguments[1]);
                // std::cout << "Field created " << command.arguments[0] << "x" << command.arguments[1] << std::endl;
                // } catch (const std::exception& e) {
                // std::cerr << e.what() << std::endl;
                // }
                break;
            }
            case InputCommands::CreateShips: {
                std::vector<size_t> lengths;  // num of ships of each length (1-4)
                lengths.reserve(10);
                for (size_t i = 0; i < command.arguments.size(); i++) {
                    for (int j = 0; j < command.arguments[i]; j++) {
                        lengths.push_back(command.arguments.size() - i);
                    }
                }
                // try {
                game.createShips(lengths.size(), lengths.data());
                // std::cout << "Ships created 4:" << command.arguments[0] << " 3:" << command.arguments[1] << " 2:" << command.arguments[2]
                //           << " 1:" << command.arguments[3] << std::endl;
                // } catch (const std::exception& e) {
                // std::cerr << e.what() << std::endl;
                // }
                break;
            }
            case InputCommands::PlaceShip:
                // try {
                game.placeShip(command.arguments[0], command.arguments[1], static_cast<ShipOrientation>(command.arguments[2]));
                // std::cout << "Ship placed at " << command.arguments[0] << "x" << command.arguments[1] << " o:" << command.arguments[2] << std::endl;
                // } catch (const std::exception& e) {
                // std::cerr << e.what() << std::endl;
                // }
                break;
            case InputCommands::InitAiPlayer:
                game.initAiPlayer();
                break;
            case InputCommands::Attack:
                // try {
                game.attack(command.arguments[0], command.arguments[1]);
                // std::cout << "Attacked at " << command.arguments[0] << "x" << command.arguments[1] << std::endl;
                // } catch (const std::exception& e) {
                // std::cerr << e.what() << std::endl;
                // }
                break;
            case InputCommands::UseAbility:
                // try {
                // AbilityType a = game.getPendingAbilityType();
                game.useAbility(command.arguments[0], command.arguments[1]);
                // if (a == AbilityType::Scanner) {
                //     std::cout << "Scanner used at " << command.arguments[0] << "x" << command.arguments[1] << std::endl;
                //     std::cout << "Scanner result: " << game.getPlayer().getAbilityResults().ScannerShipFound << std::endl;
                // }
                // if (a == AbilityType::DoubleDamage) {
                //     std::cout << "DoubleDamage used" << std::endl;
                // }
                // if (a == AbilityType::Bombard) {
                //     std::cout << "Bombard used" << std::endl;
                // }
                // } catch (const std::exception& e) {
                // std::cerr << e.what() << std::endl;
                // }
                break;
            case InputCommands::ResetGame:
                game.resetGame();
                break;
            case InputCommands::SaveGame:
                // try {
                game.saveGame();
                // std::cout << "Game saved successfully." << std::endl;
                // } catch (const std::exception& e) {
                // std::cerr << "Failed to save game: " << e.what() << std::endl;
                // }
                break;
            case InputCommands::LoadGame:
                // try {
                game.loadGame();
                // std::cout << "Game loaded successfully." << std::endl;
                // } catch (const std::exception& e) {
                // std::cerr << "Failed to load game: " << e.what() << std::endl;
                // }
                break;
            case InputCommands::Exit:
                game.exit();
                break;
            default:
                break;
        }
        // command.command = InputCommands::Invalid;
    }

    Game& game;
    InputHandler input_handler;
};

#endif  // GAMECONTROLLER_HPP