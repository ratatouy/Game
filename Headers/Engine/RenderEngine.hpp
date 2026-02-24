#ifndef RENDERENGINE_HPP
#define RENDERENGINE_HPP

#include <SFML/Graphics.hpp>


class RenderEngine {
public:
    RenderEngine(const char* title, int width, int height);
    RenderEngine(const RenderEngine&) = delete;
    RenderEngine& operator=(const RenderEngine&) = delete;

    ~RenderEngine();

private:
    static bool instantiated_;
    sf::RenderWindow* window;
};

#endif