#ifndef ENTITY_HPP
#define ENTITY_HPP

#include <SFML/Graphics.hpp>

#include "Events/Event.hpp"
#include "Events/BasicEvents/EventA.hpp"
#include "Events/CustomEvent.hpp"

class Scene; // Forward Declaration of Scene


/** Base class for all entities */
class Entity {

protected:
    Scene* current_scene; /**< Pointer to the current scene */
    const char* name;     /**< Name of the entity */


public:
    Entity() = delete;

    /** Lowest Constructor
     * 
     * @param name Name of the entity
     */
    Entity(const char* name) : name(name) {};


    /** Set the current scene of the entity
     * 
     * @param scene Pointer to the scene
     */
    void setScene(Scene* scene);


    /** Set the name of the entity
     * 
     * @param name Name of the entity
     */
    void setName(const char* name) {this->name = name;}


    /** Get the name of the entity
     * 
     * @returns Name of the entity
     */
    const char* getName() {return this->name;}

    virtual void processEvent(EventA* event);
    virtual void processEvent(CustomEvent* event);

    virtual void update();
    virtual void render(sf::RenderWindow* window);
};


#endif