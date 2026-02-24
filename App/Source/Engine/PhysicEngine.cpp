#include "Engine/PhysicEngine.hpp"

namespace PhysicEngine {
    sf::Clock clock;

    uint FPS = 60;               // Frames per second //
    uint deltaTime = 1000 / FPS; // Time between two frames //

    /**
     * @details Creates the clock
     */
    void init() {clock = sf::Clock();}

    /**
     * @details Restarts the clock and wait till the next frame
     * only wait if the time between two frames is less than the desired time (deltaTime)
     */
    void tick() {
        sf::Time elapsed = clock.restart();
        if (elapsed.asMilliseconds() < deltaTime) {
            sf::sleep(sf::milliseconds(deltaTime - elapsed.asMilliseconds()));
        }
    }
}