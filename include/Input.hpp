#ifndef INPUTHANDLER_HPP
#define INPUTHANDLER_HPP

#include <iostream>
#include <istream>
#include <unordered_map>

#include "InputCommands.hpp"

class StreamInput {
    std::unordered_map<char, InputCommands> command_map;

    std::istream& input_stream;

    InputCommand command;
    // const Stage& current_stage;
    // void scanCommand();
    // void scanArguments();
    void loadCommandsMapping();

   public:
    StreamInput(std::istream& input_stream = std::cin);
    const InputCommand& getCommand() const;
    void processInput();
};

#endif  // INPUTHANDLER_HPP