#include "Entity/Player/Player.hpp"
#include "Scenes/Scene.hpp"
#include "Events/BasicEvents/SpawnEntityEvent.hpp"

#include <iostream>
#include <memory>


void Player::update() {}


void Player::attack() {
    std::cout << "Raptorjesus von Behfeur calls upon his Rechauffeur in hope to anihilate his ArchNemesis" << std::endl;
    std::cout << "\"RECHAUFFEUR STRKE !!!!\"" << std::endl;

    Projectile* player_proj = new Projectile("player_proj", transformable_->getPosition(), {0.5f,0.f});
    player_proj->getEntitySprite()->AddSprite("cato", "assets/Sprites/cato.png");


    current_scene_->throwEvent(new SpawnEntityEvent(player_proj));
    transformable_->rotate(45);
}
