#ifndef PHYSICENGINE_HPP
#define PHYSICENGINE_HPP

#include <SFML/System.hpp>

/**
 * @namespace PhysicEngine
 * 
 * @brief The Physics Engine to Manage Physics (Physic Constants, Timers, etc.)
 */
namespace PhysicEngine {
    extern sf::Clock clock;

    extern uint FPS;       // Frames per second //
    extern uint deltaTime; // Time between two frames //

    /**
     * @brief Inits the PhysicEngine, Required for the PhysicEngine to work
     */
    void init();

    /**
     * @brief Ticks the PhysicEngine, limiting the framerate
     */
    void tick();
}

#endif