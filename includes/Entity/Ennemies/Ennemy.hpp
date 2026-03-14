#ifndef ENNEMY_HPP
#define ENNEMY_HPP

#include <iostream>

#include "Entity/Entity.hpp"
#include "Events/Event.hpp"
#include "Events/CustomEvents/HitEvent.hpp"

#include "Components/BasicComponents/TransformableComponent.hpp"
#include "Components/BasicComponents/EntitySpriteComponent.hpp"


class Ennemy : public Entity {

private:
    int health_;


public:
    Ennemy(const char* name, int health = 7) : Entity(name), health_(health) {}
    Ennemy(const char* name, TransformableComponent* transform, int health = 7) : Entity(name, transform), health_(health) {};
    Ennemy(const char* name, TransformableComponent* transform, EntitySpriteComponent* sprites, int health = 7) : Entity(name, transform, sprites), health_(health) {};
    

    void update() override;

    void processEvent(CustomEvent* event) override;

    void getHit(int damage);
};

#endif