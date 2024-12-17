#ifndef INPUTHANDLER_HPP
#define INPUTHANDLER_HPP

#include <unordered_map>

#include "InputCommands.hpp"

class TerminalInput {
    std::unordered_map<char, InputCommands> command_map;

    InputCommand command;
    // const Stage& current_stage;
    void initField();
    void initShips();
    void placeShip();

   public:
    // TerminalInput(const Stage& current_stage);
    TerminalInput();
    const InputCommand& getCommand() const;
    void processInput();
    void scanCommand();
    void scanArguments();
    void loadCommandsMapping();
};

#endif  // INPUTHANDLER_HPP