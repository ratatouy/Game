#include <iostream>
#include <queue>
#include <assert.h>

#include "Events/EventHandler.hpp"
#include "Scenes/Scene.hpp"


bool EventHandler::instantiated_ = false;


EventHandler::~EventHandler() {
    // std::cout << "Destroy EventHandler" << std::endl;
    instantiated_ = false;
    while (!eventQueue.empty()) {
        delete eventQueue.front();
        eventQueue.pop();
    }
}


void EventHandler::setCurrentScene(Scene* scene) {
    currentScene = scene;
}


EventHandler::EventHandler() {
    assert(!instantiated_);
    instantiated_ = true;
}


bool EventHandler::isEmpty() {
    return eventQueue.empty();
}


void EventHandler::addEvent(Event* event) {
    // std::cout << "Added An Event to the Queue" << std::endl;
    eventQueue.push(event);
}

void EventHandler::processEvent() {
    if (!eventQueue.empty()) {

        // std::cout << "Processing Event" << std::endl;

        EventA* Ea = dynamic_cast<EventA*>(eventQueue.front());
        if (Ea) {
            std::cout << "Processing Event A"<<std::endl;
            currentScene->processEvent(Ea);
            eventQueue.pop();
            delete Ea;
            return;
        }
        

        CustomEvent* Ec = dynamic_cast<CustomEvent*>(eventQueue.front());
        if (Ec) {
            // std::cout << "Processing Custom Event"<<std::endl;
            currentScene->processEvent(Ec);
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