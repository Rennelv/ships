#include "GameState.hpp"

#include <fstream>
#include <iostream>


GameState::GameState() : player(), player2(), ai_controller(player2), current_stage(Stage::NOT_STARTED) {
}

Player& GameState::getPlayer() {
    return player;
}

Player& GameState::getPlayer2() {
    return player2;
}

AiPlayer& GameState::getAiController() {
    return ai_controller;
}

Stage& GameState::getCurrentStage() {
    return current_stage;
}

void GameState::saveGame() {
    std::ofstream file("save.txt");
    if (!file.is_open()) {
        throw std::runtime_error("Cannot open file");
    }
    file << *this;
    file.close();
}

void GameState::loadGame() {
    std::ifstream file("save.txt");
    if (!file.is_open()) {
        throw std::runtime_error("Cannot open file");
    }
    file >> *this;
    file.close();
}

std::ostream& operator<<(std::ostream& os, const GameState& game_state) {
    os << "+++===GameState===+++\n";
    os << game_state.player;
    os << game_state.player2;
    os << static_cast<int>(game_state.current_stage) << '\n';
    os << "+++===End GameState===+++\n";
    return os;
}

std::istream& operator>>(std::istream& is, GameState& game_state) {
    std::string line;
    is >> std::ws;
    std::getline(is, line);
    if (line != "+++===GameState===+++") {
        throw std::invalid_argument("Invalid save file");
    }
    is >> game_state.player;
    is >> game_state.player2;
    int current_stage;
    is >> current_stage;
    game_state.current_stage = static_cast<Stage>(current_stage);
    is >> std::ws;
    std::getline(is, line);
    if (line != "+++===End GameState===+++") {
        throw std::invalid_argument("Invalid save file");
    }
    return is;
}