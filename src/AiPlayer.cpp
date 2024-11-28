#include "AiPlayer.hpp"

#include <cstddef>
#include <cstdlib>
#include <random>

#include "Enums.hpp"

AiPlayer::AiPlayer(Player &player) : controlled_player(player) {
}

void AiPlayer::createField(int width, int height) {
    controlled_player.createField(width, height);
}

void AiPlayer::createShipManager(size_t count, size_t *lengths) {
    controlled_player.createShipManager(count, lengths);
}

void AiPlayer::placeShipsRandom() {
    size_t ship_count = controlled_player.getShipCount();
    size_t field_width = controlled_player.getField().getWidth();
    size_t field_height = controlled_player.getField().getHeight();
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis_width(0, field_width - 1);
    std::uniform_int_distribution<> dis_height(0, field_height - 1);
    size_t i = 0;

    while (i < ship_count) {
        size_t x = dis_width(gen);
        size_t y = dis_height(gen);
        ShipOrientation orientation = static_cast<ShipOrientation>(rand() % 2);
        // Try to place the ship, if it fails, try again
        size_t attempts = 0;
        while (attempts < 1000) {
            try {
                controlled_player.placeShipByIndex(i, x, y, orientation);
                break;
            } catch (std::exception &e) {
                // retry with new coordinates
                x = dis_width(gen);
                y = dis_height(gen);
                attempts++;
            }
        }
        // If it fails 1000 times, recreate the field and start over kill me
        if (attempts >= 1000) {
            controlled_player.createField(field_width, field_height);
            i = 0;
            continue;
        }
        i++;
    }
}

void AiPlayer::attackRandom(Player &target_player) {
    size_t field_width = target_player.getField().getWidth();
    size_t field_height = target_player.getField().getHeight();

    std::random_device rd;
    std::mt19937 gen(rd());

    std::vector<std::pair<size_t, size_t>> available_points;

    for (size_t x = 0; x < field_width; ++x) {
        for (size_t y = 0; y < field_height; ++y) {
            if ((target_player.getField().getCellVisibilityState(x, y) == CellVisibilityState::UNKNOWN) ||
                ((target_player.getField().getCellVisibilityState(x, y) == CellVisibilityState::SHIP) &&
                 (target_player.getField().getShipSegmentState(x, y) != ShipSegmentState::DESTROYED))) {
                available_points.emplace_back(x, y);
            }
        }
    }

    if (!available_points.empty()) {
        std::uniform_int_distribution<> dis_points(0, available_points.size() - 1);
        auto point = available_points[dis_points(gen)];
        controlled_player.attack(target_player, point.first, point.second, 1, true);
    }
}

Player &AiPlayer::getPlayer() {
    return controlled_player;
}

void AiPlayer::reset() {
    // reset ai player
    size_t old_width = controlled_player.getField().getWidth();
    size_t old_height = controlled_player.getField().getHeight();
    createField(old_width, old_height);

    std::vector<size_t> old_lengths;
    for (size_t i = 0; i < controlled_player.getShipCount(); ++i) {
        old_lengths.push_back(controlled_player.getShipLength(i));
    }

    createShipManager(old_lengths.size(), old_lengths.data());
    placeShipsRandom();
}