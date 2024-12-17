#ifndef INPUTCOMMANDS_HPP
#define INPUTCOMMANDS_HPP

#include <vector>

enum class InputCommands {
    Invalid = -1,  // k
    CreateField,   // width, height
    CreateShips,   // vector num of ships of each length (1-4) at index
    PlaceShip,     // index, x, y, orientation
    InitAiPlayer,  // none
    Attack,        // x, y
    UseAbility,    // x, y
    ResetGame,     // none
    SaveGame,      // none
    LoadGame,      // none
    Exit,          // none
};

struct InputCommand {
    InputCommands command;
    std::vector<int> arguments;
};

#endif  // INPUTCOMMANDS_HPP