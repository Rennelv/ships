#ifndef GAMECONTROLLER_HPP
#define GAMECONTROLLER_HPP

#include <cstddef>
#include <vector>

#include "Abilities/AbilityType.hpp"
#include "Game.hpp"
#include "InputCommands.hpp"

template <typename InputHandler>
class GameController {
   public:
    GameController(Game& game, InputHandler& inputHandler) : game_(game), inputHandler_(inputHandler) {
    }

    void processInput() {
        std::cout << "Game stage: " << static_cast<int>(game_.getCurrentStage()) << std::endl;
        inputHandler_.processInput();
        const InputCommand& command = inputHandler_.getCommand();
        executeCommand(command);
    }

   private:
    void executeCommand(const InputCommand& command) {
        switch (command.command) {
            case InputCommands::CreateField: {
                try {
                    game_.createField(command.arguments[0], command.arguments[1]);
                    std::cout << "Field created " << command.arguments[0] << "x" << command.arguments[1] << std::endl;
                } catch (const std::exception& e) {
                    std::cerr << e.what() << std::endl;
                }
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
                try {
                    game_.createShips(lengths.size(), lengths.data());
                    std::cout << "Ships created 4:" << command.arguments[0] << " 3:" << command.arguments[1] << " 2:" << command.arguments[2]
                              << " 1:" << command.arguments[3] << std::endl;
                } catch (const std::exception& e) {
                    std::cerr << e.what() << std::endl;
                }
                break;
            }
            case InputCommands::PlaceShip:
                try {
                    game_.placeShip(command.arguments[0], command.arguments[1], static_cast<ShipOrientation>(command.arguments[2]));
                    std::cout << "Ship placed at " << command.arguments[0] << "x" << command.arguments[1] << " o:" << command.arguments[2] << std::endl;
                } catch (const std::exception& e) {
                    std::cerr << e.what() << std::endl;
                }
                break;
            case InputCommands::InitAiPlayer:
                game_.initAiPlayer();
                break;
            case InputCommands::Attack:
                try {
                    game_.attack(command.arguments[0], command.arguments[1]);
                    std::cout << "Attacked at " << command.arguments[0] << "x" << command.arguments[1] << std::endl;
                } catch (const std::exception& e) {
                    std::cerr << e.what() << std::endl;
                }
                break;
            case InputCommands::UseAbility:
                try {
                    AbilityType a =  game_.getPendingAbilityType();
                    game_.useAbility(command.arguments[0], command.arguments[1]);
                    if (a == AbilityType::Scanner) {
                        std::cout << "Scanner used at " << command.arguments[0] << "x" << command.arguments[1] << std::endl;
                        std::cout << "Scanner result: " << game_.getPlayer().getAbilityResults().ScannerShipFound << std::endl;
                    }
                    if (a == AbilityType::DoubleDamage) {
                        std::cout << "DoubleDamage used" << std::endl;
                    }
                    if (a == AbilityType::Bombard) {
                        std::cout << "Bombard used" << std::endl;
                    }
                } catch (const std::exception& e) {
                    std::cerr << e.what() << std::endl;
                }
                break;
            case InputCommands::ResetGame:
                game_.resetGame();
                break;
            case InputCommands::SaveGame:
                try {
                    game_.saveGame();
                    std::cout << "Game saved successfully." << std::endl;
                } catch (const std::exception& e) {
                    std::cerr << "Failed to save game: " << e.what() << std::endl;
                }
                break;
            case InputCommands::LoadGame:
                try {
                    game_.loadGame();
                    std::cout << "Game loaded successfully." << std::endl;
                } catch (const std::exception& e) {
                    std::cerr << "Failed to load game: " << e.what() << std::endl;
                }
                break;
            case InputCommands::Exit:
                game_.exit();
                break;
            default:
                break;
        }
        // command.command = InputCommands::Invalid;
    }

    Game& game_;
    InputHandler& inputHandler_;
};

#endif  // GAMECONTROLLER_HPP