#include "Scenes/Scene.hpp"
#include "Game.hpp"

#include <string.h>
#include <iostream>

Scene::Scene() {};

Scene::~Scene()
{
    // std::cout << "Destroy Scene" << std::endl;
    for (auto ent : entity_map_) {
        delete ent.second;
    }
};


void Scene::addEntity(Entity* entity)
{
    entity_map_[entity->getName()] = entity; // doesn't check for duplicity //
    entity->setScene(this);
}


Entity* Scene::getEntity(const char* name)
{
    for (auto ent : entity_map_) {
        if(strcmp(ent.first, name) == 0)
            return ent.second;
    }
    return nullptr;
}


void Scene::processEvent(SceneTransitionEvent* event)
{
    for (auto entity : entity_map_)
    {
        entity.second->processEvent(event);
    }
    processEventFunc(event);
}

void Scene::processEvent(CustomEvent* event)
{
    for (auto entity : entity_map_)
    {
        entity.second->processEvent(event);
    }
    processEventFunc(event);
};


void Scene::throwEvent(Event* event)
{
    game_->throwEvent(event);
}


void Scene::update()
{
    std::cout << "Scene Updating" << std::endl;
    updateEntities();
}


void Scene::updateEntities()
{
    std::cout << "| Updating Entities" << std::endl;
    for (std::pair<const char*, Entity*> entity_pair : entity_map_)
    {
        std::cout << "| | Updating Entity " << entity_pair.first << std::endl;
        entity_pair.second->update();
        entity_pair.second->getEntitySprite()->update();
    }
}