#ifndef AIPLAYER_HPP
#define AIPLAYER_HPP

#include "Player.hpp"

class AiPlayer {
    Player &controlled_player;

   public:
    AiPlayer(Player &player);

    void createField(int width, int height);
    void createShipManager(size_t count, size_t *lengths);
    void placeShipsRandom();
    void attackRandom(Player &targetPlayer);
    const Player &getPlayer() const;
    void reset();
};

#endif  // AIPLAYER_HPP
