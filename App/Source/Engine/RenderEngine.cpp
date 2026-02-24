#include "Engine/RenderEngine.hpp"

namespace RenderEngine {
    sf::RenderWindow* window;

    /**
     * @brief Initializes the RenderEngine
     * 
     * @details Creates the window
     */
    void init() {
        // window = new sf::RenderWindow(sf::VideoMode(960, 480), "Hello World");
        window = new sf::RenderWindow(sf::VideoMode(1920, 1080), "Hello World");
    }
}