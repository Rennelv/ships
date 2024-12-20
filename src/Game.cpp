#include "Game.hpp"
#include <cstddef>

#include "Abilities/AbilityType.hpp"
#include "GameState.hpp"

Game::Game()
    : game_state(),
      player(game_state.getPlayer()),
      player2(game_state.getPlayer2()),
      ai_controller(game_state.getAiController()),
      current_stage(game_state.getCurrentStage()) {
    current_ship_index = 0;
}

void Game::createField(int width, int height) {
    if (current_stage == Stage::CREATING_FIELD) {
        player.createField(width, height);
        nextStage();
    } else {
        throw std::invalid_argument("It is not time to create field");
    }
}

void Game::createShips(size_t count, size_t* lengths) {
    if (current_stage == Stage::CREATING_SHIPS) {
        player.createShipManager(count, lengths);
        nextStage();
    } else {
        throw std::invalid_argument("It is not time to create ships");
    }
}

void Game::placeShipByIndex(size_t index, int x, int y, ShipOrientation orientation) {
    player.placeShipByIndex(index, x, y, orientation);
}

void Game::placeShip(int x, int y, ShipOrientation orientation) {
    if (current_stage == Stage::PLACING_SHIPS) {
        placeShipByIndex(current_ship_index, x, y, orientation);
        current_ship_index++;
        if (player.getShipCount() == current_ship_index) {
            initAiPlayer();
            nextStage();
        }
    } else {
        throw std::invalid_argument("It is not time to place ships");
    }
}

void Game::initAiPlayer() {
    ai_controller.createField(player.getField().getWidth(), player.getField().getHeight());
    std::vector<size_t> ship_lengths(player.getShipCount());
    for (size_t i = 0; i < player.getShipCount(); ++i) {
        ship_lengths[i] = player.getShipLength(i);
    }
    ai_controller.createShipManager(player.getShipCount(), ship_lengths.data());
    ai_controller.placeShipsRandom();
}

void Game::attack(int x, int y) {
    if (current_stage == Stage::PLAYER_TURN) {
        player.attack(player2, x, y, 1, true);
        current_stage = Stage::AI_TURN;
    } else {
        throw std::invalid_argument("It is not player's turn");
    }
    if (current_stage == Stage::AI_TURN) {
        ai_controller.attackRandom(player);
        current_stage = Stage::PLAYER_TURN;
    } else {
        throw std::invalid_argument("It is not AI's turn");
    }
}

void Game::useAbility(int x, int y) {
    if (current_stage == Stage::PLAYER_TURN) {
        // if (player.getPendingAbilityType() == AbilityType::Scanner) {
        //     if (player.scanner_is_active) {
        //         player.useAbility(player2, x, y);
        //         player.scanner_is_active = false;
        //         return;
        //     } else {
        //         player.scanner_is_active = true;
        //     }
        // }
        player.useAbility(player2, x, y);
    } else {
        throw std::invalid_argument("It is not player's turn");
    }
}

void Game::resetGame() {
    current_stage = Stage::NOT_STARTED;
}

const Player& Game::getPlayer() const {
    return player;
}

const Player& Game::getPlayer2() const {
    return player2;
}

const AiPlayer& Game::getAiController() const {
    return ai_controller;
}

Stage Game::getCurrentStage() const {
    return current_stage;
}

void Game::nextStage() {
    if (current_stage == Stage::NOT_STARTED) {
        current_stage = Stage::CREATING_FIELD;
    } else if (current_stage == Stage::CREATING_FIELD) {
        current_stage = Stage::CREATING_SHIPS;
    } else if (current_stage == Stage::CREATING_SHIPS) {
        current_stage = Stage::PLACING_SHIPS;
    } else if (current_stage == Stage::PLACING_SHIPS) {
        current_stage = Stage::PLAYER_TURN;
    } else if (current_stage == Stage::PLAYER_TURN) {
        current_stage = Stage::AI_TURN;
    } else if (current_stage == Stage::AI_TURN) {
        current_stage = Stage::PLAYER_TURN;
    } else if (current_stage == Stage::GAME_OVER) {
        current_stage = Stage::NOT_STARTED;
    }
}

AbilityType Game::getPendingAbilityType() const {
    if (current_stage != Stage::PLAYER_TURN) {
        throw std::invalid_argument("It is not player's turn");
    }
    return player.getPendingAbilityType();
}

void Game::saveGame() {
    game_state.saveGame();
}

void Game::loadGame() {
    game_state.loadGame();
}

void Game::exit() {
    current_stage = Stage::EXIT;
}

void Game::checkWin() {
    if (current_stage == Stage::PLAYER_TURN || current_stage == Stage::AI_TURN) {
        if (player2.getAliveCount() == 0) {
            player2.reset();
            ai_controller.placeShipsRandom();
        }
        if (player.getAliveCount() == 0) {
            current_stage = Stage::NOT_STARTED;
            nextStage();
        }
    }
}

size_t Game::getCurrShipIndex() const {
    return current_ship_index;
}