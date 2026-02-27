#ifndef ENTITY_HPP
#define ENTITY_HPP

#include <SFML/Graphics.hpp>

#include "Events/Event.hpp"
#include "Events/BasicEvents/EventA.hpp"
#include "Events/CustomEvent.hpp"

class Scene; // Forward Declaration of Scene


/**
 \class Entity

 \brief Base class for all entities
 
 \warning "update" and "render" methods NEED to be overrided
 
 */
class Entity {
protected:
    Scene* current_scene;
    const char* name;

public:
    Entity() = delete;
    Entity(const char* n) : name(n) {};

    void setScene(Scene* scene);

    void setName(const char* n) {name = n;}
    const char* getName() {return this->name;}

    virtual void processEvent(EventA* event);
    virtual void processEvent(CustomEvent* event);

    virtual void update();
    virtual void render(sf::RenderWindow* window);
};


#endif