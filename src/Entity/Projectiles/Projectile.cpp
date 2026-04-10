#include "Entity/Projectile/Projectile.hpp"
#include <iostream>

Projectile::Projectile(const std::string& name, sf::Vector2f position, sf::Vector2f speed) : CollidableEntity(name), speed_(speed)
{
    transformable->setPosition(position);
};

Projectile::~Projectile() {}

void Projectile::update()
{
    transformable->setPosition(transformable->getPosition() + speed_);
    transformable->rotate(1);
}

void Projectile::processCollision(const CollidableEntity* other)
{}