#ifndef GAMERENDERER_HPP
#define GAMERENDERER_HPP

template <typename Renderer>
class GameRenderer {
   public:
    GameRenderer(Renderer& renderer) : renderer(renderer) {
    }

    void render() {
        // renderer.update();
        renderer.render();
    }

    void onGameStateChanged() {
        render();
    }

   private:
    Renderer& renderer;
};

#endif  // GAMERENDERER_HPP