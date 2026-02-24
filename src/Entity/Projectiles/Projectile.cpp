#include "Entity/Projectile/Projectile.hpp"
#include <iostream>

Projectile::Projectile(const char* n, sf::Vector2f p, sf::Vector2f sp) : Entity(n), speed(sp)
{
    transformable = new TransformableComponent();
    transformable->setPosition(p);

    sprites = new EntitySpriteComponent(transformable);
};

void Projectile::update()
{
    transformable->setPosition(transformable->getPosition() + speed);
    transformable->rotate(1);
    sprites->update();
}

void Projectile::render(sf::RenderWindow* window)
{
    this->sprites->render(window);
}