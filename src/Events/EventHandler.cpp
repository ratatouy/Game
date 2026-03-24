#include <iostream>
#include <queue>

#include "Events/EventHandler.hpp"
#include "Game.hpp"

#include "logger.hpp"

bool EventHandler::instantiated_ = false;


EventHandler::~EventHandler() {
    // std::cout << "Destroy EventHandler" << std::endl;
    while (!eventQueue.empty()) {
        delete eventQueue.front();
        eventQueue.pop();
    }

    instantiated_ = false;
}


void EventHandler::setGame(Game* game) {
    game_ = game;
}


EventHandler::EventHandler() {
    if (instantiated_) {
        throw std::runtime_error("EventHandler already instantiated");
    }
    
    instantiated_ = true;
}


bool EventHandler::isEmpty() {
    return eventQueue.empty();
}


void EventHandler::addEvent(Event* event) {
    Logger::log(EVENT_HANDLER, DEBUG, "Adding event");
    eventQueue.push(event);
}

void EventHandler::processEvent() {
    if (!eventQueue.empty()) {

        SceneTransitionEvent* Et = dynamic_cast<SceneTransitionEvent*>(eventQueue.front());
        if (Et) {
            Logger::log(EVENT_HANDLER, DEBUG, "Processing SceneTransition Event");
            game_->processEvent(Et);
            eventQueue.pop();
            delete Et;
            return;
        }
        
        
        SpawnEntityEvent* Es = dynamic_cast<SpawnEntityEvent*>(eventQueue.front());
        if (Es) {
            Logger::log(EVENT_HANDLER, DEBUG, "Processing SpawnEntity Event");
            game_->processEvent(Es);
            eventQueue.pop();
            delete Es;
            return;
        }


        CustomEvent* Ec = dynamic_cast<CustomEvent*>(eventQueue.front());
        if (Ec) {
            Logger::log(EVENT_HANDLER, DEBUG, "Processing Custom Event");
            game_->processEvent(Ec);
            eventQueue.pop();
            delete Ec;
            return;
        }
    }
}

Event* EventHandler::getCurrentEvent() {
    if (!eventQueue.empty()) {
        Event* event = eventQueue.front();
        eventQueue.pop();
        return event;
    }
    return nullptr;
}