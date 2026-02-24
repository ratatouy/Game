#ifndef PROJECTILE_HPP
#define PROJECTILE_HPP

#include "Entity/Entity.hpp"

#include "Components/BasicComponents/TransformableComponent.hpp"
#include "Components/BasicComponents/EntitySpriteComponent.hpp"


class Projectile : public Entity {
private:
    TransformableComponent* transformable;
    EntitySpriteComponent* sprites;

    sf::Vector2f speed;

public:
    Projectile(const char* n, sf::Vector2f p = {0,0}, sf::Vector2f sp = {0,0});

    void update() override;
};


#endif