#include "Scenes/Scene.hpp"
#include "Transitions/Transition.hpp"
#include "Game.hpp"
#include "Engine/RenderEngine.hpp"

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


void Scene::addEntity(Entity* entity)
{
    Logger::log(SCENE, DEBUG, "ADDING entity " + entity->getName());
    entity_map_[entity->getName()] = entity; // doesn't check for duplicity //
    Logger::log(SCENE, DEBUG, "ADDING entity " + entity->getName());
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
    Entity* entity = nullptr;

    // search for the entity
    for (auto ent : entity_map_) {
        if (name == ent.first)
            entity = ent.second;
    }

    if (entity == nullptr)
        Logger::log(SCENE, WARNING, "Extract : Entity " + name + " not found");

    entity_map_.erase(name);
    return entity;
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
        sf::Transformable* player_transform = getEntity("player")->transformable;
        if (player_transform == nullptr)
            throw(std::runtime_error("Player transform not found"));
        
        if (transition_pair.second->checkTransition())
            throwEvent(std::make_unique<SceneTransitionEvent>(transition_pair.second->getTargetName()));
    }
    return false;
}


void Scene::attachDrawablesToRenderEngine(RenderEngine* renderEngine)
{
    for (auto it : entity_map_)
    {
        auto data = it.second->entitySprite->GetSpriteData();
        
        // run through the map of the entitySprite
        for (auto it2 = data->begin(); it2 != data->end(); it2++)
        {
            std::string drawable_name = it.first + std::string("_") + (std::string)it2->first;

            renderEngine->addDrawable(drawable_name, (sf::Drawable*)&it2->second.sprite);
        }
    }
}