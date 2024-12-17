#ifndef STATE_HPP
#define STATE_HPP

#include <SFML/Graphics.hpp>
#include <SFML/Window/Event.hpp>

class RendererState {
   public:
    virtual ~RendererState() = default;
    virtual void update() = 0;
    virtual void render(sf::RenderWindow &window) = 0;
};

#endif  // STATE_HPP