#include "Game.hpp"
#include "Events/EventHandler.hpp"
#include "Scenes/Scene.hpp"

#include "logger.hpp"

#include <iostream>

bool Game::instantiated_ = false;

Game::Game()
{
    if (instantiated_) {
        throw std::runtime_error("Game already instantiated");
    }
    eventHandler_ = new EventHandler(this);
    renderEngine_ = new RenderEngine(this, "Game", 920, 480);

    instantiated_ = true;
}

Game::~Game()
{
    delete eventHandler_;
    delete renderEngine_;
    instantiated_ = false;
}

void Game::loadScene(const std::string& name)
{
    Logger::log(GAME, DEBUG, "Loading scene"+name);
    Scene* sc = LoadScene(name);
    this->setActiveScene(sc);
}

void Game::throwEvent(std::unique_ptr<Event> event)
{
    Logger::log(GAME, DEBUG, "Throwing event");
    eventHandler_->addEvent(std::move(event));
}


void Game::processEvent(SceneTransitionEvent* event)
{
    active_scene_->processEvent(event);
    this->processEventFunc(event);
}
void Game::processEventFunc(SceneTransitionEvent* event)
{
    Logger::log(GAME, INFO, "processing SceneTransition Event");
    // this->setActiveScene(event->getScene());
}

void Game::processEvent(SpawnEntityEvent* event)
{
    Logger::log(GAME, DEBUG, "dispatching SpawnEntity Event");
    this->processEventFunc(event);
}
void Game::processEventFunc(SpawnEntityEvent* event)
{
    Logger::log(GAME, DEBUG, "processing SpawnEntity Event");
    this->addEntity(event->getEntity());
}

void Game::processEvent(CustomEvent* event)
{
    active_scene_->processEvent(event);
}
void Game::processEventFunc(CustomEvent* event) {}



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

    auto data = entity->entitySprite->GetSpriteData();

    // run through the map of the entitySprite
    for (auto it = data->begin(); it != data->end(); it++)
    {
        std::string drawable_name = entity->getName() + std::string("_") + (std::string)it->first;

        renderEngine_->addDrawable(drawable_name, (sf::Drawable*)&std::get<0>(it->second));
    }
}
