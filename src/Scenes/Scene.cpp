#include "Scenes/Scene.hpp"
#include "Events/EventHandler.hpp"

#include <string.h>
#include <iostream>

Scene::Scene() {};

Scene::~Scene()
{
    // std::cout << "Destroy Scene" << std::endl;
    for (auto ent : entityMap) {
        delete ent.second;
    }
    delete eventHandler;
};

void Scene::setEventHandler(EventHandler* handler)
{
    eventHandler = handler;
};


void Scene::addEntity(Entity* entity)
{
    entityMap[entity->getName()] = entity; // doesn't check for duplicity //
    entity->setScene(this);
}


Entity* Scene::getEntity(const char* name)
{
    for (auto ent : entityMap) {
        if(strcmp(ent.first, name) == 0)
            return ent.second;
    }
    return nullptr;
}


void Scene::processEvent(EventA* event)
{;
    for (auto entity : entityMap)
    {
        entity.second->processEvent(event);
    }
    processEventFunc(event);
}


void Scene::processEvent(CustomEvent* event)
{
    for (auto entity : entityMap)
    {
        entity.second->processEvent(event);
    }
    processEventFunc(event);
};


void Scene::throwEvent(Event* event)
{
    eventHandler->addEvent(event);
}


void Scene::updateEntity()
{
    for (std::pair<const char*, Entity*> entity_pair : entityMap)
    {
        entity_pair.second->update();
    }
}

void Scene::render(sf::RenderWindow* window)
{
    for (auto entity : entityMap)
    {
        entity.second->render(window);
    }
}