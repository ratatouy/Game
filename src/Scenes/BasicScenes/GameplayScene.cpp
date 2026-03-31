#include "Scenes/BasicScenes/GameplayScene.hpp"

void GameplayScene::update()
{
    updateEntities();
}

void GameplayScene::updateEntities()
{
    for (std::pair<std::string, Entity*> entity_pair : entity_map_)
    {
        entity_pair.second->update();
        entity_pair.second->entitySprite->update();
    }
}