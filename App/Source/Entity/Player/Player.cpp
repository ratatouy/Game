#include "Entity/Player/Player.hpp"
#include "Scenes/Scene.hpp"

#include <iostream>
#include <memory>


void Player::update() {
    // std::cout << "Player Updating" << std::endl;
    attack();
    sprites->update();
}

void Player::render(sf::RenderWindow* window) {
    // std::cout << "Player Rendering" << std::endl;
    this->sprites->render(window);
}

void Player::attack() {
    std::cout << "Raptorjesus von Behfeur calls upon his Rechauffeur in hope to anihilate his ArchNemesis" << std::endl;
    std::cout << "\"RECHAUFFEUR STRKE !!!!\"" << std::endl;

    current_scene->addEntity(new Projectile("pr", transform->getPosition(), {1,0}), "pr");
    transform->rotate(45);
}
