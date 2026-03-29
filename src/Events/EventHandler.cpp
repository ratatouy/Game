#include <iostream>
#include <queue>

#include "Events/EventHandler.hpp"
#include "Game.hpp"

#include "logger.hpp"

bool EventHandler::instantiated_ = false;


EventHandler::EventHandler(Game* game) {
    if (instantiated_) {
        throw std::runtime_error("EventHandler already instantiated");
    }
    game_ = game;
    
    instantiated_ = true;
}


EventHandler::~EventHandler() {
    std::cout << "Destroy EventHandler" << std::endl;
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
    Logger::log(EVENT_HANDLER, DEBUG, "Adding event");
    eventQueue.push(std::move(event));
}

void EventHandler::processEvent() {
    if (!eventQueue.empty()) {

        std::unique_ptr<Event> ev = _getEventToProcess();

        SceneTransitionEvent* Et = dynamic_cast<SceneTransitionEvent*>(ev.get());
        if (Et) {
            Logger::log(EVENT_HANDLER, DEBUG, "Processing SceneTransition Event");
            game_->processEvent(Et);
            return;
        }
        
        
        SpawnEntityEvent* Es = dynamic_cast<SpawnEntityEvent*>(ev.get());
        if (Es) {
            Logger::log(EVENT_HANDLER, DEBUG, "Processing SpawnEntity Event");
            game_->processEvent(Es);
            return;
        }


        CustomEvent* Ec = dynamic_cast<CustomEvent*>(ev.get());
        if (Ec) {
            Logger::log(EVENT_HANDLER, DEBUG, "Processing Custom Event");
            game_->processEvent(Ec);
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