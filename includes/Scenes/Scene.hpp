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
    /// \warning Deprecated (game is set when loading the scene in game::loadScene)
    ///
    /// \param game Reference to the Game
    ////////////////////////////////////////////////////////////
    void setGame(Game* game) {game_ = game;}

    ////////////////////////////////////////////////////////////
    /// \brief Returns the origin of the scene
    ///
    /// \returns Origin of the scene
    ////////////////////////////////////////////////////////////
    const sf::Vector2i& getOrigin() {return origin_;}

    ////////////////////////////////////////////////////////////
    /// \brief Returns the size of the scene
    ///
    /// \returns Size of the scene
    ////////////////////////////////////////////////////////////
    const sf::Vector2u& getSize() const {return size_;}
    
    ////////////////////////////////////////////////////////////
    /// \brief returns a reference to the Entity according to its name
    ///
    /// Returns nullptr if not found.
    ///
    /// \param name name of the entity
    ///
    /// \returns pointer to the entity, nullptr if not found
    ///
    /// \see Entity
    ///
    /// \todo Make this const
    ////////////////////////////////////////////////////////////
    const Entity* getEntity(std::string name) const;

    ////////////////////////////////////////////////////////////
    /// \brief Extracts an entity from the scene
    ///
    /// This removes the entity from the map
    /// 
    /// \param name name of the entity
    ///
    /// \returns pointer to the entity, nullptr if not found
    ////////////////////////////////////////////////////////////
    Entity* extractEntity(std::string name);

    ////////////////////////////////////////////////////////////
    /// \brief CustomEvent process distributor
    ///
    /// Distributes the CustomEvent to the objects that need it,
    /// which depends on the type of the Scene and of the CustomEvent.
    ///
    /// \param event CustomEvent
    ////////////////////////////////////////////////////////////
    virtual void distributeEvent(CustomEvent* event);

    ////////////////////////////////////////////////////////////
    /// \brief Process a CustomEvent
    ///
    /// What it does depends on the type of the Scene and the CustomEvent.
    ///
    /// \param event CustomEvent
    ////////////////////////////////////////////////////////////
    virtual void processEvent(CustomEvent* event) {};

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
    void throwEvent(std::unique_ptr<Event> event);

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
    virtual void update() = 0;
    
    ////////////////////////////////////////////////////////////
    /// \brief Checks if a transition should be activated
    ///
    /// \returns True if a transition should be activated
    ////////////////////////////////////////////////////////////
    bool checkTransition();

protected:
    ////////////////////////////////////////////////////////////
    /// Member Data
    ////////////////////////////////////////////////////////////
    Game* game_;                                                  ///< Reference to the game object
    std::string name_;                                            ///< Name of the current_scene
    std::unordered_map<std::string, Transition*> transition_map_; ///< Map of the Transitions
    std::unordered_map<std::string, Entity*> entity_map_;         ///< List of the entities according to their names
    sf::Vector2i origin_;                                         ///< Origin of the current scene in the global space
    sf::Vector2u size_;                                           ///< Size of the current scene

};

#endif