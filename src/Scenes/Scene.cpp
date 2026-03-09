#include "Scenes/Scene.hpp"
#include "Events/EventHandler.hpp"
#include "Engine/RenderEngine.hpp"

#include <string.h>
#include <iostream>

Scene::Scene() {};

Scene::~Scene()
{
    // std::cout << "Destroy Scene" << std::endl;
    for (auto ent : entityMap_) {
        delete ent.second;
    }
    delete eventHandler_;
};


void Scene::addEntity(Entity* entity)
{
    entityMap_[entity->getName()] = entity; // doesn't check for duplicity //
    entity->setScene(this);
}


Entity* Scene::getEntity(const char* name)
{
    for (auto ent : entityMap_) {
        if(strcmp(ent.first, name) == 0)
            return ent.second;
    }
    return nullptr;
}


void Scene::processEvent(SceneTransitionEvent* event)
{
    for (auto entity : entityMap_)
    {
        entity.second->processEvent(event);
    }
    processEventFunc(event);
}

void Scene::processEvent(CustomEvent* event)
{
    for (auto entity : entityMap_)
    {
        entity.second->processEvent(event);
    }
    processEventFunc(event);
};


void Scene::throwEvent(Event* event)
{
    eventHandler_->addEvent(event);
}


void Scene::update()
{
    updateEntities();
}


void Scene::render()
{
    renderEntities();
}


void Scene::updateEntities()
{
    for (std::pair<const char*, Entity*> entity_pair : entityMap_)
    {
        entity_pair.second->update();
    }
}

void Scene::renderEntities()
{
    for (auto entity : entityMap_)
    {
        entity.second->render(renderEngine_->getWindow());
    }
}