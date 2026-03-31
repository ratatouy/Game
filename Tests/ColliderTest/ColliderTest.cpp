#include "Entity/Player/Player.hpp"
#include "Entity/Ennemies/Ennemy.hpp"
#include "Entity/CollidableEntity.hpp"

#include "Scenes/BasicScenes/MenuScene.hpp"

#include "Events/EventHandler.hpp"

#include "Engine/PhysicsEngine.hpp"
#include "Engine/RenderEngine.hpp"

#include "Game.hpp"

#include "logger.hpp"


int main() {
    CollidableEntity entity("test", nullptr);
    std::cout << entity.transformable->getPosition().x << std::endl;

    return 0;
}