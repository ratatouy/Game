#include <iostream>
#include <string.h>

#include "Entity/Ennemies/Ennemy.hpp"

void Ennemy::processEvent(CustomEvent* event) {
    // std::cout << "Ennemy Processing HitEvent" << std::endl;
    HitEvent* H = dynamic_cast<HitEvent*>(event);

    if (H) {
        HitData* data = (HitData*) H->getData();

        if (strcmp(data->target, name) == 0) {
            HitData* Hd = (HitData*) H->getData();
            getHit(data->damage);
        }
        else return;
    }
    else return;
}

void Ennemy::getHit(int damage) {
    std::cout << "|||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||" << std::endl;
    std::cout << "ARCHNEMESIS | Lilimanjaro's Scream Bends °Ti¤e & S_p@Ce !!!" << std::endl;
    std::cout << "he dies" << std::endl;
    health -= damage;
}

void Ennemy::update() {
    // std::cout << "Ennemy Updating" << std::endl;
}

void Ennemy::render(sf::RenderWindow* window) {
    // std::cout << "Ennemy Rendering" << std::endl;
    this->sprites->render(window);
}