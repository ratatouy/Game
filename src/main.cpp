#include "Entity/Player/Player.hpp"
#include "Entity/Ennemies/Ennemy.hpp"

#include "Scenes/BasicScenes/MenuScene.hpp"

#include "Events/EventHandler.hpp"

#include "Engine/PhysicsEngine.hpp"
#include "Engine/RenderEngine.hpp"

#include "Game.hpp"

#include "logger.hpp"

int main() {
    Logger::restart();

    // PhysicEngine* pEngine = new PhysicEngine(0);

    Game* game = Game::getInstance();
    game->loadScene("a1");

    sf::Transformable* raptorTransform = new sf::Transformable();
    raptorTransform->setPosition({0, 200});
    raptorTransform->setScale({0.2f, 0.2f});
    EntitySpriteComponent* raptorSprite = new EntitySpriteComponent(raptorTransform);
    raptorSprite->addSprite("body", "assets/Sprites/raptorjesus.jpeg");
    raptorSprite->addSprite("rechauffeur", "assets/Sprites/rechauffeur.png");
    ColliderComponent* raptorCollider = new ColliderComponent(raptorTransform);
    raptorCollider->setSize({100, 100});

    Player* raptor = new Player("player", raptorTransform, raptorSprite, raptorCollider);
    
    game->addEntity(raptor);

    /**sf::Transformable* liliTransformable = new sf::Transformable();
    liliTransformable->setPosition({400, 0});
    liliTransformable->setScale({0.1f, 0.1f});
    EntitySpriteComponent* liliSprite = new EntitySpriteComponent(liliTransformable);
    liliSprite->addSprite("body", "assets/Sprites/lilimanjaro.jpg");
    Ennemy* lili = new Ennemy("lili", liliTransformable, liliSprite);


    game->addEntity(lili); */

    sf::Event event;

    while (game->getRenderEngine()->getWindow()->isOpen())
    {
        while (game->getRenderEngine()->getWindow()->pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                game->getRenderEngine()->getWindow()->close();
            }
            else if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Space)
            {
                Player* player = (Player*)game->getActiveScene()->getEntity("player");
                player->attack();
            }
            else if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Right)
            {
                game->getActiveScene()->getEntity("player")->transformable->move({10, 0});
                game->getEventHandler()->addEvent(std::make_unique<SceneTransitionEvent>("a1"));
            }
            else if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Left)
            {
                game->getActiveScene()->getEntity("player")->transformable->move({-10, 0});
                game->getEventHandler()->addEvent(std::make_unique<SceneTransitionEvent>("a2"));
            }
        }
        
        while (!game->getEventHandler()->isEmpty())
        {
            game->getEventHandler()->processEvent();
            std::cout << game->getActiveScene()->getEntity("player")->entitySprite->get_nb_sprites() << std::endl;
        }
        

        game->getRenderEngine()->getWindow()->clear(sf::Color(125,0,125,0));
        game->update();
        game->render();
        game->getRenderEngine()->getWindow()->display();

    }

    return 0;
}