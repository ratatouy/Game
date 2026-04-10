#include "Engine/PhysicsEngine.hpp"

PhysicEngine* PhysicEngine::instance_ = nullptr;
bool PhysicEngine::instantiated_ = false;


PhysicEngine* PhysicEngine::getInstance(unsigned int fps)
{
    if (!instantiated_)
        instance_ = new PhysicEngine(fps);
    return instance_;
}

PhysicEngine::PhysicEngine(unsigned int fps)
{
    if (instantiated_) {
        throw std::runtime_error("PhysicEngine already instantiated");
    }
    instantiated_ = true;

    FPS = fps;

    (FPS == 0) ? deltaTime = 0 : deltaTime = 1000/FPS;

    clock = sf::Clock();
    session_runtime_clock = sf::Clock();
}


void PhysicEngine::tick()
{
    // get elapsed time since last frame
    sf::Time elapsed = clock.getElapsedTime();
    // wait until next frame
    if (clock.getElapsedTime().asMilliseconds() < deltaTime) {
        sf::sleep(sf::milliseconds(deltaTime - elapsed.asMilliseconds()));
    }
    // reset clock
    clock.restart();
}