/// Declaration
#include "Entity/Player/Player.hpp"

#include "Scenes/Scene.hpp"
#include "Transitions/Transition.hpp"
#include "Transitions/BasicTransitions/BorderTransition.hpp"

#include "logger.hpp"

#include <iostream>
#include <memory>

/// Events
#include "Events/BasicEvents/SpawnEntityEvent.hpp"
#include "Events/BasicEvents/DeleteEntityEvent.hpp"
#include "Events/BasicEvents/SceneTransitionEvent.hpp"

void Player::update() {}

void Player::processCollision(const CollidableEntity* other)
{
    Logger::log(PLAYER, INFO, "COLLISION WITH " + other->getName());
}


void Player::processEvent(SceneTransitionEvent* event)
{
    Logger::log(PLAYER, INFO, "Player process transition");
    const Transition* tr = event->getTransition();

    const HorizontalTransition* Hr_tr = (const HorizontalTransition*)tr;
    if (Hr_tr)
    {
        (Hr_tr->isGoingRight()) ?
            this->transformable->move(this->getColliderComponent()->getSize().x, 0)
            :
            this->transformable->move(-this->getColliderComponent()->getSize().x, 0);
    }
    const VerticalTransition* Vr_tr = (const VerticalTransition*)tr;
    if (Vr_tr)
    {
        (Vr_tr->isGoingDown()) ?
            this->transformable->move(0, this->getColliderComponent()->getSize().y)
            :
            this->transformable->move(0, -this->getColliderComponent()->getSize().x);
    }
}


void Player::attack()
{
    Logger::log(PLAYER, INFO, "\"RECHAUFFEUR STRKE !!!!\"");

    projectile_ = new Projectile("player_proj", transformable->getPosition(), {0.5f,0.f});
    projectile_->entitySprite->addSprite("cato", "assets/Sprites/cato.png");

    current_scene_->throwEvent(std::make_unique<SpawnEntityEvent>(projectile_));
    transformable->rotate(45);
}
