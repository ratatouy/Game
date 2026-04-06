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
    sf::Transformable* tr1 = new sf::Transformable();
    ColliderComponent* col1 = new ColliderComponent(tr1);
    tr1->setPosition(10, 10);     // Global position of the entity is now 10,10
    col1->setOffset({-10, 0});    // The collider is offset by -10,0
    col1->setSize({30, 10});      // The collider has a size of 30,10
    Ennemy ent1("en1", tr1);
    ent1.setCollider(col1);

    sf::Transformable* tr2 = new sf::Transformable();
    ColliderComponent* col2 = new ColliderComponent(tr2);
    tr2->setPosition(20, 10);   // Global position of the entity is now 20,10
    // This Entity has an offset of 0 and a size of {1,1}
    Ennemy ent2("en2", tr2);
    ent2.setCollider(col2);

    std::cout << ent2.isCollidingWith(&ent1);
    std::cout << ent1.isCollidingWith(&ent2); // Should output the same thing (1 with those values)

    return 0;
}