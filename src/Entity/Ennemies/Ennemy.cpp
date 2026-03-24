#include <iostream>
#include <string.h>

#include "Entity/Ennemies/Ennemy.hpp"

void Ennemy::processEvent(CustomEvent* event) {
    HitEvent* H = dynamic_cast<HitEvent*>(event);

    if (H) {
        HitData* data = (HitData*) H->getData();

        if (strcmp(data->target, name_) == 0) {
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
