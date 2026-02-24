#include "Components/BasicComponents/TransformableComponent.hpp"
#include "Components/BasicComponents/EntitySpriteComponent.hpp"

#include "Entity/Entity.hpp"
#include "Entity/Player/Player.hpp"
#include "Entity/Ennemies/Ennemy.hpp"

#include "Scenes/Scene.hpp"
#include "Scenes/BasicScenes/MenuScene.hpp"

#include "Events/Event.hpp"
#include "Events/EventHandler.hpp"

#include "Engine/PhysicEngine.hpp"
#include "Engine/RenderEngine.hpp"

int main() {
    MenuScene* menu = new MenuScene();
    EventHandler* evHandler = new EventHandler();

    menu->setEventHandler(evHandler);
    evHandler->setCurrentScene(menu);


    TransformableComponent* raptorTransform = new TransformableComponent();
    EntitySpriteComponent* raptorSprite = new EntitySpriteComponent(raptorTransform);
    raptorSprite->AddSprite("Sprites/raptorjesus.jpeg");
    Player* raptor = new Player("raptor", raptorTransform, raptorSprite);


    TransformableComponent* liliTransformable = new TransformableComponent();
    EntitySpriteComponent* liliSprite = new EntitySpriteComponent(liliTransformable);
    raptorSprite->AddSprite("Sprites/lilimanjaro.jpg");
    Ennemy* lili = new Ennemy("lili", liliTransformable, liliSprite);


    menu->addEntity(raptor, "raptor");
    menu->addEntity(lili, "lili");


    menu->updateEntity();


    return 0;
}