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

int main() {
    // PhysicEngine* pEngine = new PhysicEngine(0);
    RenderEngine* rEngine = new RenderEngine("Game", 920, 480);


    MenuScene* menu = new MenuScene();
    EventHandler* evHandler = new EventHandler();

    menu->setEventHandler(evHandler);
    evHandler->setCurrentScene(menu);

    rEngine->setScene(menu);
    menu->setRenderEngine(rEngine);

    // pEngine->setScene(menu);
    // menu->setPhysicEngine(pEngine);


    TransformableComponent* raptorTransform = new TransformableComponent();
    raptorTransform->setPosition({0, 200});
    raptorTransform->setScale({0.2f, 0.2f});
    EntitySpriteComponent* raptorSprite = new EntitySpriteComponent(raptorTransform);
    raptorSprite->AddSprite("assets/Sprites/raptorjesus.jpeg");

    Player* raptor = new Player("raptor", raptorTransform, raptorSprite);


    TransformableComponent* liliTransformable = new TransformableComponent();
    liliTransformable->setPosition({400, 0});
    liliTransformable->setScale({0.1f, 0.1f});
    EntitySpriteComponent* liliSprite = new EntitySpriteComponent(liliTransformable);
    liliSprite->AddSprite("assets/Sprites/lilimanjaro.jpg");
    Ennemy* lili = new Ennemy("lili", liliTransformable, liliSprite);


    menu->addEntity(raptor);
    menu->addEntity(lili);

    sf::Event event;

    while (rEngine->getWindow()->isOpen())
    {
        while (rEngine->getWindow()->pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                rEngine->getWindow()->close();
            }
            else if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Space)
            {
                Player* pl = (Player*)menu->getEntity("raptor");
                pl->attack();
            }
            else if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Right)
            {
                Player* pl = (Player*)menu->getEntity("raptor");
                pl->getTransformable()->move({10, 0});
            }
            else if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Left)
            {
                Player* pl = (Player*)menu->getEntity("raptor");
                pl->getTransformable()->move({-10, 0});
            }
        }

        rEngine->getWindow()->clear(sf::Color(125,0,125,0));
        menu->update();
        menu->render();
        rEngine->getWindow()->display();
    }


    return 0;
}