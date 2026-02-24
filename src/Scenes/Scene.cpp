#include "Scenes/Scene.hpp"
#include "Events/EventHandler.hpp"

#include <string.h>
#include <iostream>

Scene::Scene() {};

Scene::~Scene() {
    // std::cout << "Destroy Scene" << std::endl;
    for (auto ent : entityMap) {
        delete ent.second;
    }
    delete eventHandler;
};

void Scene::setEventHandler(EventHandler* handler) {
    eventHandler = handler;
};


void Scene::addEntity(Entity* entity, const char* name) {
    entityMap[name] = entity; // doesn't check for duplicity //
    entity->setScene(this);
}


Entity* Scene::getEntity(const char* name) {
    for (auto ent : entityMap) {
        if(strcmp(ent.first, name))
            return ent.second;
    }
    return nullptr;
}


void Scene::processEvent(EventA* event) {;
    for (auto entity : entityMap) {
        entity.second->processEvent(event);
    }
    processEventFunc(event);
}


void Scene::processEvent(CustomEvent* event) {
    for (auto entity : entityMap) {
        //filter(target, entity)//
        entity.second->processEvent(event);
    }
    processEventFunc(event);
};


void Scene::throwEvent(Event* event) {
    eventHandler->addEvent(event);
}


void Scene::updateEntity() {
    for (auto entity : entityMap) {
        entity.second->update();
    }
}

void Scene::render(sf::RenderWindow* window) {
    for (auto entity : entityMap) {
        entity.second->render(window);
    }
}