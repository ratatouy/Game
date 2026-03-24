#ifndef SCENE_HPP
#define SCENE_HPP

////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
#include <memory>

#include <SFML/Graphics.hpp>

#include "Entity/Entity.hpp"
#include "Events/Event.hpp"
#include "Events/CustomEvent.hpp"
#include "Events/BasicEvents/SceneTransitionEvent.hpp"


class Game;       // Forward Declaration of Game //

class Transition; // Forward Declaration of Transition //


////////////////////////////////////////////////////////////
/// \brief Base class for all Scenes
///
/// All of the game is just a collection of scenes.
/// Each scene is a box, with a collection of :
/// \li transitions
/// \li entities
///
/// \note missing elements :
/// \li Transitions
/// \li Solid Tiles
/// \li Decorations (bg assets/...)
////////////////////////////////////////////////////////////
class Scene
{
public:
    ////////////////////////////////////////////////////////////
    /// \brief Constructs a Scene from its origin and size
    ///
    /// \param origin Origin of the current scene in the global space
    ///
    /// \param size Size of the current scene
    ////////////////////////////////////////////////////////////
    Scene(sf::Vector2i origin, sf::Vector2u size) : origin_(origin), size_(size) {};

    ////////////////////////////////////////////////////////////
    /// \brief Default destructor
    ////////////////////////////////////////////////////////////
    ~Scene();

    ////////////////////////////////////////////////////////////
    /// \brief Set the reference to the Game
    ///
    /// \param game Reference to the Game
    ////////////////////////////////////////////////////////////
    void setGame(Game* game) {game_ = game;}

    ////////////////////////////////////////////////////////////
    /// \brief Returns the origin of the scene
    ///
    /// \returns Origin of the scene
    ////////////////////////////////////////////////////////////
    sf::Vector2i getOrigin() {return origin_;}

    ////////////////////////////////////////////////////////////
    /// \brief Returns the size of the scene
    ///
    /// \returns Size of the scene
    ////////////////////////////////////////////////////////////
    sf::Vector2u getSize() {return size_;}
    
    ////////////////////////////////////////////////////////////
    /// \brief returns an Entity according to its name
    ///
    /// Returns nullptr if not found.
    ///
    /// \param name name of the entity
    ///
    /// \returns pointer to the entity, nullptr if not found
    ///
    /// \see Entity
    ////////////////////////////////////////////////////////////
    Entity* getEntity(const char* name);

    ////////////////////////////////////////////////////////////
    /// \brief SceneTransitionEvent process distributor
    ///
    /// Distributes the SceneTransitionEvent to the objects that need it :
    /// \li this
    /// \li entities
    ///
    /// \param event SceneTransitionEvent
    ///
    /// \see SceneTransitionEvent
    ////////////////////////////////////////////////////////////
    virtual void processEvent(SceneTransitionEvent* event);

    ////////////////////////////////////////////////////////////
    /// \brief Process a SceneTransitionEvent
    ///
    /// Will unload itself.
    ///
    /// \param event SceneTransitionEvent
    ////////////////////////////////////////////////////////////
    virtual void processEventFunc(SceneTransitionEvent* event) {};

    ////////////////////////////////////////////////////////////
    /// \brief CustomEvent process distributor
    ///
    /// Distributes the CustomEvent to the objects that need it,
    /// which depends on the type of the CustomEvent.
    ///
    /// \param event CustomEvent
    ////////////////////////////////////////////////////////////
    virtual void processEvent(CustomEvent* event);

    ////////////////////////////////////////////////////////////
    /// \brief Process a CustomEvent
    ///
    /// What it does depends on the type of the CustomEvent.
    ///
    /// \param event CustomEvent
    ////////////////////////////////////////////////////////////
    virtual void processEventFunc(CustomEvent* event) {};

    ////////////////////////////////////////////////////////////
    /// \brief Throws the event to the parent game object
    ///
    /// This doesn't actually care about the type of the event, it just passes it to the game object
    ///, which will then pass it to the EventHandler to add it to the queue.
    ///
    /// \param event event to throw
    ///
    /// \see Game::throwEvent
    ////////////////////////////////////////////////////////////
    void throwEvent(Event* event);

    ////////////////////////////////////////////////////////////
    /// \brief Adds an entity to the scene
    ///
    /// The entity has to be fully constructed before adding it to the scene,
    /// this functions just takes a pointer to the entity.
    ///
    /// \warning Beware of deleting the local pointer to the entity when using this method.
    ///
    /// \param entity entity to add
    ////////////////////////////////////////////////////////////
    void addEntity(Entity* entity);

    ////////////////////////////////////////////////////////////
    /// \brief Updates the scene
    ////////////////////////////////////////////////////////////
    virtual void update();
    
    ////////////////////////////////////////////////////////////
    /// \brief Checks if a transition should be activated
    ///
    /// \returns True if a transition should be activated
    ////////////////////////////////////////////////////////////
    bool checkTransition();

    ////////////////////////////////////////////////////////////
    /// \brief Updates all of the entities
    ////////////////////////////////////////////////////////////
    void updateEntities();



private:
    ////////////////////////////////////////////////////////////
    // Attributes
    ////////////////////////////////////////////////////////////
    Game* game_;                                                  ///< Reference to the game object
    const char* name_;                                            ///< Name of the current_scene
    std::unordered_map<const char*, Transition*> transition_map_; ///< Map of the Transitions
    std::unordered_map<const char*, Entity*> entity_map_;         ///< List of the entities according to their names
    sf::Vector2i origin_;                                         ///< Origin of the current scene in the global space
    sf::Vector2u size_;                                           ///< Size of the current scene

};

#endif