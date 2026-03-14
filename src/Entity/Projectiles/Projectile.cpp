#include "Entity/Projectile/Projectile.hpp"
#include <iostream>

Projectile::Projectile(const char* name, sf::Vector2f position, sf::Vector2f speed) : Entity(name), speed_(speed)
{
    transformable_ = new TransformableComponent();
    transformable_->setPosition(position);

    entitySprite_ = new EntitySpriteComponent(transformable_);
};

void Projectile::update()
{
    transformable_->setPosition(transformable_->getPosition() + speed_);
    transformable_->rotate(1);
    entitySprite_->update();
}
