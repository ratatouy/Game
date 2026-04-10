#include <iostream>

#include "Entity/Ennemies/Ennemy.hpp"

void Ennemy::processCollision(const CollidableEntity* other)
{
    Logger::log(ENTITY, INFO, "COLLISION WITH " + other->getName());
}

void Ennemy::processEvent(CustomEvent* event) {
    HitEvent* H = dynamic_cast<HitEvent*>(event);

    if (H) {
        HitData* data = (HitData*) H->getData();

        if (data->target == name_) {
            HitData* Hd = (HitData*) H->getData();
            getHit(data->damage);
        }
        else return;
    }
    else return;
}

void Ennemy::getHit(int damage) {
    health_ -= damage;
}

void Ennemy::update() {}
