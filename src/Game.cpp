#include "Game.hpp"
#include "Events/EventHandler.hpp"
#include "Scenes/Scene.hpp"
#include "Entity/Player/Player.hpp"

#include "logger.hpp"

#include <iostream>

bool Game::instantiated_ = false;
Game* Game::instance_ = nullptr;

Game::Game()
{
    this->eventHandler_ = EventHandler::getInstance(this);
    this->renderEngine_ = RenderEngine::getInstance(this, "Game", 920, 480);
}

Game* Game::getInstance()
{
    if (!instantiated_) {
        instance_ = new Game();
        instantiated_ = true;
        Logger::log(GAME, INFO, "INSTANTIATE Game");
    }
    return instance_;
}


Game::~Game()
{
    Logger::log(GAME, INFO, "DESTROYING Game");

    delete eventHandler_;
    delete renderEngine_;
    instantiated_ = false;
}

void Game::loadScene(const std::string& name)
{
    Logger::log(GAME, INFO, "LOADING scene \""+name+"\"");
    setActiveScene(Parser::LoadScene(name));
    active_scene_->attachDrawablesToRenderEngine(renderEngine_);
    active_scene_->setGame(this);
}

void Game::throwEvent(std::unique_ptr<Event> event)
{
    Logger::log(GAME, INFO, "THROWING event");
    eventHandler_->addEvent(std::move(event));
}


void Game::distributeEvent(SceneTransitionEvent* event)
{
    Logger::log(GAME, INFO, "DISTRIBUTING SceneTransition Event");
    this->processEvent(event);
}

void Game::processEvent(SceneTransitionEvent* event)
{
    Logger::log(GAME, INFO, "PROCESSING SceneTransition Event");
    Player* pl = active_scene_->extractEntity<Player>("player");
    pl->processEvent(event);

    if (!pl) {
        Logger::log(GAME, ERROR, "No player found in scene");
        throw std::runtime_error("No player found in scene");
    }

    delete active_scene_;
    renderEngine_->clearAll();
    loadScene(event->getTransition()->getTargetName());
    addEntity(pl);
}

void Game::distributeEvent(SpawnEntityEvent* event)
{
    Logger::log(GAME, INFO, "DISTRIBUTING SpawnEntity Event");
    this->processEvent(event);
}
void Game::processEvent(SpawnEntityEvent* event)
{
    Logger::log(GAME, INFO, "PROCESSING SpawnEntity Event");
    this->addEntity(event->getEntity());
}

void Game::distributeEvent(DeleteEntityEvent* event)
{
    Logger::log(GAME, INFO, "DISTRIBUTING DeleteEntity Event");
    this->processEvent(event);
}
void Game::processEvent(DeleteEntityEvent* event)
{
    Logger::log(GAME, INFO, "PROCESSING DeleteEntity Event");
    // extract entity from scene & delete it
    delete active_scene_->extractEntity(event->getName());

    // clear the corresponding ESC
    renderEngine_->removeESC(event->getName());
}


void Game::distributeEvent(CustomEvent* event)
{
    Logger::log(GAME, INFO, "distributeING Custom Event");
    active_scene_->distributeEvent(event);
}

void Game::processEvent(CustomEvent* event) {}



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

    renderEngine_->addESC(entity->getName(), entity->entitySprite);
}

void Game::deleteEntity(const std::string& name)
{
    delete active_scene_->extractEntity(name);

    renderEngine_->removeESC(name);
}