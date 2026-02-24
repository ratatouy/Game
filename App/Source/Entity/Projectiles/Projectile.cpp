#include "Entity/Projectile/Projectile.hpp"

Projectile::Projectile(const char* n, sf::Vector2f p, sf::Vector2f sp) : Entity(n), speed(sp)
{
    transformable = new TransformableComponent();
    transformable->setPosition(p);
};

void Projectile::update()
{
    transformable->setPosition(transformable->getPosition() + speed);
}