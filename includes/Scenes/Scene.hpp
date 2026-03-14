#ifndef SCENE_HPP
#define SCENE_HPP

#include <memory>

#include <SFML/Graphics.hpp>

#include "Entity/Entity.hpp"
#include "Events/Event.hpp"
#include "Events/CustomEvent.hpp"
#include "Events/BasicEvents/SceneTransitionEvent.hpp"

#include "Transition/Transition.hpp"


class Game;         // Forward Declaration of Game //


/** Base class for all Sscenes
 * 
 * @details the Scene is the mastermind behind everything, it links every elements together
 * It has references to the RenderEngine, the PhysicsEngine, the EventHandler and the entities
 * 
 * @note missing elements :
 * - Transitions
 * - Solid Tiles
 * - Decorations (bg assets/...)
 */
class Scene {
private:
    Game* game_;        /**< Reference to the game object */

    const char* name_;  /**< Name of the current_scene */

    std::unordered_map<const char*, Transition> transition_map_;    /**< Map of the Transitions */
    std::unordered_map<const char*, Entity*> entity_map_;           /**< List of the entities according to their names */

    

public:
    /** Only Constructor */
    Scene();
    ~Scene();


    /** game Setter
     * @param game Reference to the Game */
    void setGame(Game* game) {game_ = game;}


    /** distinct entity Getter
     * 
     * returns an entity according to its name
     * 
     * @param name name of the entity
     * 
     * @returns pointer to the entity */
    Entity* getEntity(const char* name);


    /** SceneTransitionEvent processing distributor */
    virtual void processEvent(SceneTransitionEvent* event);
    /** SceneTransitionEvent processing function */
    virtual void processEventFunc(SceneTransitionEvent* event) {};
    /** CustomEvent processing distributor */
    virtual void processEvent(CustomEvent* event);
    /** CustomEvent processing function */
    virtual void processEventFunc(CustomEvent* event) {};


    /** Throws the event to the parent game object
     * @param event event to throw */
    void throwEvent(Event* event);


    /** Adds an entity 
     * @param entity entity to add */
    void addEntity(Entity* entity);



    virtual void update();
    

    void updateEntities();
};

#endif