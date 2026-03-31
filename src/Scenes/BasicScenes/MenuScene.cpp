#include "Scenes/BasicScenes/MenuScene.hpp"

void MenuScene::update()
{
    updateEntities();
}

void MenuScene::updateEntities()
{
    for (std::pair<std::string, Entity*> entity_pair : entity_map_)
    {
        entity_pair.second->update();
        entity_pair.second->entitySprite->update();
    }
}