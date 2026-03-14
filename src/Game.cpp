#include "Game.hpp"
#include "Events/EventHandler.hpp"
#include "Scenes/Scene.hpp"

#include <iostream>

bool Game::instantiated_ = false;

Game::Game()
{
    if (instantiated_) {
        throw std::runtime_error("Game already instantiated");
    }
    instantiated_ = true;
}

void Game::throwEvent(Event* event)
{
    eventHandler_->addEvent(event);
}


void Game::processEvent(SceneTransitionEvent* event)
{
    active_scene_->processEvent(event);
}
void Game::processEventFunc(SceneTransitionEvent* event)
{
    std::cout << "Game Processing TransitionEvent" << std::endl;
}

void Game::processEvent(SpawnEntityEvent* event)
{
    this->processEventFunc(event);
}
void Game::processEventFunc(SpawnEntityEvent* event)
{
    std::cout << "Game Processing SpawnEntityEvent" << std::endl;
    this->addEntity(event->getEntity());
}

void Game::processEvent(CustomEvent* event)
{
    active_scene_->processEvent(event);
}
void Game::processEventFunc(CustomEvent* event)
{
    std::cout << "Game Processing CustomEvent" << std::endl;
}



void Game::update()
{
    active_scene_->update();
}


void Game::render()
{
    renderEngine_->render();
}


void Game::addEntity(Entity* entity)
{
    active_scene_->addEntity(entity);

    auto data = entity->getEntitySprite()->GetSpriteData();

    // run through the map of the entitySprite
    for (auto it = data->begin(); it != data->end(); it++)
    {
        std::string drawable_name = entity->getName() + std::string("_") + (std::string)it->first;

        renderEngine_->addDrawable(drawable_name, &std::get<0>(it->second));
    }
}
