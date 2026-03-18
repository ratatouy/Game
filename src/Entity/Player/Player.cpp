#include "Entity/Player/Player.hpp"
#include "Scenes/Scene.hpp"
#include "Events/BasicEvents/SpawnEntityEvent.hpp"

#include "logger.hpp"

#include <iostream>
#include <memory>


void Player::update() {}


void Player::attack() {
    Logger::log(PLAYER, INFO, "Raptorjesus von Behfeur calls upon his Rechauffeur in hope to anihilate his ArchNemesis");
    Logger::log(PLAYER, INFO, "\"RECHAUFFEUR STRKE !!!!\"");

    Projectile* player_proj = new Projectile("player_proj", transformable_->getPosition(), {0.5f,0.f});
    player_proj->getEntitySprite()->AddSprite("cato", "assets/Sprites/cato.png");


    current_scene_->throwEvent(new SpawnEntityEvent(player_proj));
    transformable_->rotate(45);
}
