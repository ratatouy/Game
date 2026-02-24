#ifndef RENDERENGINE_HPP
#define RENDERENGINE_HPP

#include <SFML/Graphics.hpp>


class RenderEngine {
public:
    RenderEngine(const char* title = "Game", int width = 920, int height = 480);
    RenderEngine(const RenderEngine&) = delete;
    RenderEngine& operator=(const RenderEngine&) = delete;

    ~RenderEngine();

    sf::RenderWindow* getWindow() {return this->window;}

private:
    static bool instantiated_;
    sf::RenderWindow* window;
};

#endif