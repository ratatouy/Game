#include <iostream>

#include "Entity/Entity.h"
#include "Components/Component.h"
#include "Components/EntitySpriteComponent.h"
#include "Components/TransformableComponent.h"

int main() {
    Entity* entity = new Entity();
    std::cout << "Entity Created" << std::endl;

    TransformableComponent* transformable = new TransformableComponent();
    std::cout << "TransformableComponent Created" << std::endl;
    EntitySpriteComponent* sprite = new EntitySpriteComponent(transformable);
    std::cout << "EntitySpriteComponent Created" << std::endl;


    entity->AddComponent(transformable);
    std::cout << "TransformableComponent Added to Entity" << std::endl;
    entity->AddComponent(sprite);
    std::cout << "EntitySpriteComponent Added to Entity" << std::endl;


    entity->GetComponent<TransformableComponent>()->setPosition({10, 10});
    std::cout << "Set Entity's Transformable Position with GetComponent Method" << std::endl;

    // std::cout << "New Position : (" << entity->GetComponent<TransformableComponent*>()->getPosition().x
    // << "," << entity->GetComponent<TransformableComponent*>()->getPosition().x << ")" << std::endl;

    return 0;
}
