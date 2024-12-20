#ifndef GAMERENDERER_HPP
#define GAMERENDERER_HPP

#include <string>
#include "Game.hpp"
template <typename Renderer>
class GameRenderer {
   public:
    GameRenderer(Game& game) : renderer(game) {
    }

    void render() {
        // renderer.update();
        renderer.render();
    }

    void printErr(std::string msg) {
        renderer.printErr(msg);
    }

   private:
    Renderer renderer;
};

#endif  // GAMERENDERER_HPP