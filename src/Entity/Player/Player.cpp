#include "Entity/Player/Player.hpp"
#include "Scenes/Scene.hpp"

#include <iostream>
#include <memory>


void Player::update() {
    // std::cout << "Player Updating" << std::endl;
    entitySprite_->update();
}

void Player::render(sf::RenderWindow* window) {
    // std::cout << "Player Rendering" << std::endl;
    this->entitySprite_->render(window);
}

void Player::attack() {
    std::cout << "Raptorjesus von Behfeur calls upon his Rechauffeur in hope to anihilate his ArchNemesis" << std::endl;
    std::cout << "\"RECHAUFFEUR STRKE !!!!\"" << std::endl;

    Projectile* player_proj = new Projectile("player_proj", transformable_->getPosition(), {0.5f,0.f});
    player_proj->sprites->AddSprite("Sprites/cato.png");
    current_scene->addEntity(player_proj);
    transformable_->rotate(45);
}
