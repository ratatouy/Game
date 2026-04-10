#ifndef ENNEMY_HPP
#define ENNEMY_HPP

////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
#include <iostream>

#include "Entity/CollidableEntity.hpp"
#include "Events/Event.hpp"
#include "Events/CustomEvents/HitEvent.hpp"

#include "Components/BasicComponents/EntitySpriteComponent.hpp"


class Ennemy : public CollidableEntity {

private:
    int health_;


public:
    Ennemy(std::string name, int health = 7) : CollidableEntity(name), health_(health) {}
    Ennemy(std::string name, sf::Transformable* transform, int health = 7) : CollidableEntity(name, transform), health_(health) {};
    Ennemy(std::string name, sf::Transformable* transform, EntitySpriteComponent* sprites, int health = 7) : CollidableEntity(name, transform, sprites), health_(health) {};
    
    void update() override;
    
    void processCollision(const CollidableEntity* other) override;

    void processEvent(CustomEvent* event) override;

    void getHit(int damage);
};

#endif