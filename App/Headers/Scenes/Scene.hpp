#ifndef SCENE_HPP
#define SCENE_HPP

#include <unordered_map>
#include <memory>

#include <SFML/Graphics.hpp>

#include "Entity/Entity.hpp"
#include "Events/Event.hpp"
#include "Events/CustomEvent.hpp"
#include "Events/BasicEvents/EventA.hpp"

class EventHandler; // Forward Declaration of EventHandler //

class Scene {
public:
    EventHandler* eventHandler;

    Scene();
    ~Scene();

    void setEventHandler(EventHandler* EventHandler);

    void addEntity(Entity* entity, const char* name);

    Entity* getEntity(const char* name);

    virtual void processEvent(EventA* event);
    virtual void processEventFunc(EventA* event) {};
    virtual void processEvent(CustomEvent* event);
    virtual void processEventFunc(CustomEvent* event) {};

    void throwEvent(Event* event);

    void updateEntity();

    void render(sf::RenderWindow* window);

private:
    std::unordered_map<const char*, Entity*> entityMap;
};

#endif