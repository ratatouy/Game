#include "Scenes/Scene.hpp"
#include "Transitions/Transition.hpp"
#include "Game.hpp"
#include "Engine/RenderEngine.hpp"
#include "Entity/Player/Player.hpp"

#include "logger.hpp"

#include <string.h>
#include <iostream>


Scene::~Scene()
{
    Logger::log(SCENE, DEBUG, "DESTROYING scene");
    for (auto ent : entity_map_) {
        delete ent.second;
    }
    entity_map_.clear();
};

void Scene::addTransition(Transition* transition)
{
    transition_map_[transition->getName()] = transition; // doesn't check for duplicity //
}

void Scene::addEntity(Entity* entity)
{
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


Entity* Scene::extractEntity(std::string name)
{
    Logger::log(SCENE, DEBUG, "EXTRACTING entity " + name);

    // search for the entity
    for (auto ent : entity_map_) {
        // Found it
        if (name == ent.first)
        {
            entity_map_.erase(name);
            return ent.second;
        }
    }
    return nullptr;
}


void Scene::distributeEvent(CustomEvent* event)
{
    Logger::log(SCENE, DEBUG, "DISTRIBUTING CustomEvent");
    for (auto entity : entity_map_)
    {
        entity.second->processEvent(event);
    }
    processEvent(event);
};


void Scene::throwEvent(std::unique_ptr<Event> event)
{
    Logger::log(SCENE, DEBUG, "THROWING event");
    game_->throwEvent(std::move(event));
}


bool Scene::checkTransition()
{
    for (auto transition_pair : transition_map_)
    {
        const Player* player = getEntity<Player>("player");
        
        if (player == nullptr)
            throw(std::runtime_error("Player transform not found"));
        
        if (transition_pair.second->checkTransition())
            throwEvent(std::make_unique<SceneTransitionEvent>(transition_pair.second));
    }
    return false;
}


void Scene::attachDrawablesToRenderEngine(RenderEngine* renderEngine)
{
    for (auto it : entity_map_)
    {
        // attach each ESCs
        renderEngine->addESC(it.second->getName(), it.second->entitySprite);
    }
}