#include "TerminalInput.hpp"

#include <fstream>
#include <iostream>
#include <limits>
#include <set>
#include <string>
#include <unordered_map>

#include "InputCommands.hpp"

// TerminalInput::TerminalInput(const Stage& current_stage) : current_stage(current_stage) {
TerminalInput::TerminalInput() {
    try {
        loadCommandsMapping();
    } catch (const std::exception& e) {
        std::cerr << e.what() << std::endl;
        command_map = {
            {'c', InputCommands::CreateField}, {'n', InputCommands::CreateShips}, {'p', InputCommands::PlaceShip},
            {'a', InputCommands::Attack},      {'u', InputCommands::UseAbility},  {'g', InputCommands::ResetGame},
            {'v', InputCommands::SaveGame},    {'l', InputCommands::LoadGame},    {'q', InputCommands::Exit},
        };
    }
}

void TerminalInput::initField() {
    std::cout << "Enter field size (x y): ";
    command.command = InputCommands::CreateField;
    scanArguments();
}

void TerminalInput::initShips() {
    std::cout << "Enter number of ships of each length (1-4): ";
    command.command = InputCommands::CreateShips;
    scanArguments();
}

void TerminalInput::placeShip() {
    std::cout << "Enter ship index, x, y, orientation: ";
    command.command = InputCommands::PlaceShip;
    scanArguments();
}

const InputCommand& TerminalInput::getCommand() const {
    return command;
}

void TerminalInput::processInput() {
    scanCommand();
    scanArguments();
}

void TerminalInput::scanCommand() {
    char command_char = std::getchar();
    while (isspace(command_char)) {
        command_char = std::getchar();
    }
    if (command_char == EOF) {
        command.command = InputCommands::Invalid;
        return;
    }
    if (command_map.find(command_char) == command_map.end()) {
        command.command = InputCommands::Invalid;
        return;
    }
    command.command = command_map.at(command_char);
}

void TerminalInput::scanArguments() {
    switch (command.command) {
        case InputCommands::CreateField:
        case InputCommands::Attack:
        case InputCommands::UseAbility: {
            int x, y;
            std::cin >> x >> y;
            command.arguments = {x, y};
            break;
        }
        case InputCommands::CreateShips: {
            int arg1, arg2, arg3, arg4;
            std::cin >> arg1 >> arg2 >> arg3 >> arg4;
            command.arguments = {arg1, arg2, arg3, arg4};
            break;
        }
        case InputCommands::PlaceShip: {
            int arg1, arg2, arg3;
            std::cin >> arg1 >> arg2 >> arg3;
            command.arguments = {arg1, arg2, arg3};
            break;
        }
        default:
            command.arguments = {};
            break;
    }
    if (std::cin.fail()) {
        command.command = InputCommands::Invalid;
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
}

void TerminalInput::loadCommandsMapping() {
    std::ifstream file("commands_mapping.txt");
    if (!file.is_open()) {
        throw std::runtime_error("Failed to open commands_mapping.txt");
    }

    std::unordered_map<char, InputCommands> temp_map;
    std::set<InputCommands> assigned_commands;
    std::set<char> assigned_keys;

    std::unordered_map<std::string, InputCommands> string_to_command = {
        {"CreateField", InputCommands::CreateField}, {"CreateShips", InputCommands::CreateShips}, {"PlaceShip", InputCommands::PlaceShip},
        {"Attack", InputCommands::Attack},           {"UseAbility", InputCommands::UseAbility},   {"ResetGame", InputCommands::ResetGame},
        {"SaveGame", InputCommands::SaveGame},       {"LoadGame", InputCommands::LoadGame},       {"Exit", InputCommands::Exit},
    };

    char key;
    std::string command;
    while (file >> key >> command) {
        if (string_to_command.find(command) == string_to_command.end()) {
            throw std::runtime_error("Invalid command name");
        }
        InputCommands cmd = string_to_command.at(command);

        if (assigned_keys.find(key) != assigned_keys.end()) {
            throw std::runtime_error("Duplicate key assignment detected");
        }
        if (assigned_commands.find(cmd) != assigned_commands.end()) {
            throw std::runtime_error("Duplicate command assignment detected");
        }

        temp_map[key] = cmd;
        assigned_keys.insert(key);
        assigned_commands.insert(cmd);
    }

    for (const auto& pair : string_to_command) {
        if (assigned_commands.find(pair.second) == assigned_commands.end()) {
            throw std::runtime_error("Not all commands have assigned keys");
        }
    }

    command_map = std::move(temp_map);
}