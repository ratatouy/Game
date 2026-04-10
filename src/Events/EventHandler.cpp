#include <iostream>
#include <queue>

#include "Events/EventHandler.hpp"
#include "Game.hpp"

#include "logger.hpp"

bool EventHandler::instantiated_ = false;
EventHandler* EventHandler::instance_ = nullptr;


EventHandler::EventHandler(Game* game) {
    game_ = game;    
}

EventHandler* EventHandler::getInstance(Game* game)
{
    if (!instantiated_) {
        Logger::log(EVENT, INFO, "INSTANTIATE EventHandler");
        instance_ = new EventHandler(game);
        instantiated_ = true;
    }
    return instance_;
}


EventHandler::~EventHandler() {
    Logger::log(EVENT, INFO, "DESTROY EventHandler");
    while (!eventQueue.empty()) {
        std::unique_ptr<Event> ev = _getEventToProcess();
        ev.reset();
    }
    instantiated_ = false;
}


void EventHandler::setGame(Game* game) {
    game_ = game;
}


bool EventHandler::isEmpty() {
    return eventQueue.empty();
}


void EventHandler::addEvent(std::unique_ptr<Event> event) {
    Logger::log(EVENT, INFO, "STACK event to queue");
    eventQueue.push(std::move(event));
}

void EventHandler::processEvent()
{

    if (!eventQueue.empty()) {

        std::unique_ptr<Event> ev = _getEventToProcess();

        SceneTransitionEvent* Et = dynamic_cast<SceneTransitionEvent*>(ev.get());
        if (Et) {
            Logger::log(EVENT, INFO, "START SceneTransitionEvent processing");
            game_->distributeEvent(Et);
            Logger::log(EVENT, INFO, "DONE SceneTransitionEvent processing");
            return;
        }
        
        SpawnEntityEvent* Es = dynamic_cast<SpawnEntityEvent*>(ev.get());
        if (Es) {
            Logger::log(EVENT, INFO, "START SpawnEntityEvent processing");
            game_->distributeEvent(Es);
            Logger::log(EVENT, INFO, "DONE SpawnEntityEvent processing");
            return;
        }

        DeleteEntityEvent* Ed = dynamic_cast<DeleteEntityEvent*>(ev.get());
        if (Ed) {
            Logger::log(EVENT, INFO, "START DeleteEntityEvent processing");
            game_->distributeEvent(Ed);
            Logger::log(EVENT, INFO, "DONE DeleteEntityEvent processing");
            return;
        }

        CustomEvent* Ec = dynamic_cast<CustomEvent*>(ev.get());
        if (Ec) {
            Logger::log(EVENT, INFO, "START CustomEvent processing");
            game_->distributeEvent(Ec);
            Logger::log(EVENT, INFO, "DONE CustomEvent processing");
            return;
        }
    }
}

std::unique_ptr<Event> EventHandler::_getEventToProcess() {
    if (!eventQueue.empty()) {
        std::unique_ptr<Event> event = std::move(eventQueue.front());
        eventQueue.pop();
        return std::move(event);
    }
    return nullptr;
}