#include "Scenes/Scene.hpp"
#include "Transitions/Transition.hpp"
#include "Game.hpp"

#include "logger.hpp"

#include <string.h>
#include <iostream>


Scene::~Scene()
{
    // std::cout << "Destroy Scene" << std::endl;
    for (auto ent : entity_map_) {
        delete ent.second;
    }
};


void Scene::addEntity(Entity* entity)
{
    Logger::log(SCENE, DEBUG, "Adding entity " + (std::string)entity->getName());
    entity_map_[entity->getName()] = entity; // doesn't check for duplicity //
    entity->setScene(this);
}


const Entity* Scene::getEntity(std::string name) const
{
    for (auto ent : entity_map_) {
        if (name == ent.first)
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

void Scene::processEventFunc(SceneTransitionEvent* event)
{
    delete this;
}

void Scene::processEvent(CustomEvent* event)
{
    for (auto entity : entity_map_)
    {
        entity.second->processEvent(event);
    }
    processEventFunc(event);
};


void Scene::throwEvent(std::unique_ptr<Event> event)
{
    Logger::log(SCENE, DEBUG, "Throwing event");
    game_->throwEvent(std::move(event));
}


void Scene::update()
{
    updateEntities();
}


bool Scene::checkTransition()
{
    for (auto transition_pair : transition_map_)
    {
        sf::Transformable* player_transform = getEntity("player")->transformable;
        if (player_transform == nullptr)
            throw(std::runtime_error("Player transform not found"));
        
        if (transition_pair.second->checkTransition())
            throwEvent(std::make_unique<SceneTransitionEvent>(transition_pair.second->getTargetName()));
    }
    return false;
}


void Scene::updateEntities()
{
    for (std::pair<std::string, Entity*> entity_pair : entity_map_)
    {
        entity_pair.second->update();
        entity_pair.second->entitySprite->update();
    }
}