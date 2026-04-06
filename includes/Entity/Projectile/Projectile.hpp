#ifndef PROJECTILE_HPP
#define PROJECTILE_HPP

#include "Entity/CollidableEntity.hpp"

#include "Components/BasicComponents/EntitySpriteComponent.hpp"


class Projectile : public CollidableEntity {
private:
    sf::Vector2f speed_;


public:
    Projectile(const std::string& name, sf::Vector2f position = {0,0}, sf::Vector2f speed = {0,0});

    void update() override;

    void processCollision(const CollidableEntity* other) override;
};


#endif