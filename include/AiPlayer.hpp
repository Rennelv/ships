#ifndef AIPLAYER_HPP
#define AIPLAYER_HPP

#include "Player.hpp"

class AiPlayer {
    Player &controlled_player;

   public:
    AiPlayer(Player &player);

    void createField(int width, int height);
    void createShipManager(size_t count, size_t *lengths);
    void placeShips();
    void attack(Player &targetPlayer);
    Player &getPlayer();
    void reset();
};

#endif  // AIPLAYER_HPP
