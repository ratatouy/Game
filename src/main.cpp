#include "Components/BasicComponents/TransformableComponent.hpp"
#include "Components/BasicComponents/EntitySpriteComponent.hpp"

#include "Entity/Entity.hpp"
#include "Entity/Player/Player.hpp"
#include "Entity/Ennemies/Ennemy.hpp"

#include "Scenes/Scene.hpp"
#include "Scenes/BasicScenes/MenuScene.hpp"

#include "Events/Event.hpp"
#include "Events/EventHandler.hpp"

#include "Engine/PhysicsEngine.hpp"
#include "Engine/RenderEngine.hpp"

#include "Game.hpp"

int main() {
    // PhysicEngine* pEngine = new PhysicEngine(0);
    MenuScene* menu = new MenuScene();
    EventHandler* evHandler = new EventHandler();
    RenderEngine* rEngine = new RenderEngine("Game", 920, 480);


    Game* game = new Game();

    game->setEventHandler(evHandler);
    evHandler->setGame(game);

    rEngine->setGame(game);
    game->setRenderEngine(rEngine);

    game->setActiveScene(menu);
    menu->setGame(game);


    TransformableComponent* raptorTransform = new TransformableComponent();
    raptorTransform->setPosition({0, 200});
    raptorTransform->setScale({0.2f, 0.2f});
    EntitySpriteComponent* raptorSprite = new EntitySpriteComponent(raptorTransform);
    raptorSprite->AddSprite("body", "assets/Sprites/raptorjesus.jpeg");
    raptorSprite->AddSprite("rechauffeur", "assets/Sprites/rechauffeur.png");

    Player* raptor = new Player("raptor", raptorTransform, raptorSprite);


    TransformableComponent* liliTransformable = new TransformableComponent();
    liliTransformable->setPosition({400, 0});
    liliTransformable->setScale({0.1f, 0.1f});
    EntitySpriteComponent* liliSprite = new EntitySpriteComponent(liliTransformable);
    liliSprite->AddSprite("body", "assets/Sprites/lilimanjaro.jpg");
    Ennemy* lili = new Ennemy("lili", liliTransformable, liliSprite);


    game->addEntity(raptor);
    game->addEntity(lili);


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
                Player* pl = (Player*)game->getActiveScene()->getEntity("raptor");
                pl->attack();
            }
            else if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Right)
            {
                std::cout << "yo" << game->getActiveScene()->getEntity("raptor")->getTransformable()->getPosition().x << std::endl;
                game->getActiveScene()->getEntity("raptor")->getTransformable()->move({10, 0});
                std::cout << "yo" << game->getActiveScene()->getEntity("raptor")->getTransformable()->getPosition().x << std::endl;
            }
            else if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Left)
            {
                game->getActiveScene()->getEntity("raptor")->getTransformable()->move({-10, 0});
            }
        }
        
        while (!game->getEventHandler()->isEmpty())
        {
            game->getEventHandler()->processEvent();
        }
        

        game->getRenderEngine()->getWindow()->clear(sf::Color(125,0,125,0));
        game->update();
        game->render();
        game->getRenderEngine()->getWindow()->display();
    }


    return 0;
}