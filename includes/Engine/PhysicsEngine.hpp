#ifndef PHYSICENGINE_HPP
#define PHYSICENGINE_HPP

#include <SFML/System.hpp>


/** The Physics Engine to Manage Physics (Physic Constants, Timers, etc.) */
class PhysicEngine {
public:
    // Constructor //
    PhysicEngine(uint FPS);


    // @brief Ticks the PhysicEngine according to the framerate //
    void tick();


private:
    static bool instantiated_;

    sf::Clock clock;

    uint FPS;       // Frames per second //
    uint deltaTime; // Time between two frames //
};

#endif