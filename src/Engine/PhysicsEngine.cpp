#include "Engine/PhysicsEngine.hpp"

bool PhysicEngine::instantiated_ = false;

PhysicEngine::PhysicEngine(uint FPS)
{
    if (instantiated_) {
        throw std::runtime_error("PhysicEngine already instantiated");
    }
    instantiated_ = true;

    this->FPS = FPS;

    (FPS == 0) ? deltaTime = 0 : deltaTime = 1000/FPS;

    clock = sf::Clock();
}


void PhysicEngine::tick()
{
    sf::Time elapsed = clock.restart();
    if (elapsed.asMilliseconds() < deltaTime) {
        sf::sleep(sf::milliseconds(deltaTime - elapsed.asMilliseconds()));
    }
}