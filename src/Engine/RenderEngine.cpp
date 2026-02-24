#include "Engine/RenderEngine.hpp"


bool RenderEngine::instantiated_ = false;


RenderEngine::RenderEngine(const char* title = "Game", int width = 0, int height = 0)
{
    if (instantiated_) {
        throw std::runtime_error("RenderEngine already instantiated");
    }
    instantiated_ = true;

    window = new sf::RenderWindow(sf::VideoMode(width, height), title);
}

RenderEngine::~RenderEngine()
{
    delete window;
    instantiated_ = false;
}