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

    Projectile* player_proj = new Projectile("player_proj", transformable->getPosition(), {0.5f,0.f});
    player_proj->entitySprite->AddSprite("cato", "assets/Sprites/cato.png");

    std::unique_ptr<Event> e_ptr = std::make_unique<SpawnEntityEvent>(player_proj);
    current_scene_->throwEvent(std::move(e_ptr));
    transformable->rotate(45);
}
