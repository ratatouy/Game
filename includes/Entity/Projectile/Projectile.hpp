#ifndef PROJECTILE_HPP
#define PROJECTILE_HPP

#include "Entity/Entity.hpp"

#include "Components/BasicComponents/TransformableComponent.hpp"
#include "Components/BasicComponents/EntitySpriteComponent.hpp"


class Projectile : public Entity {
private:
    sf::Vector2f speed_;


public:
    Projectile(const char* name, sf::Vector2f position = {0,0}, sf::Vector2f speed = {0,0});


    void update() override;
};


#endif