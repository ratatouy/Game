#ifndef SCENE_HPP
#define SCENE_HPP

////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
#include <SFML/Graphics.hpp>
#include <memory>

#include "Entity/Entity.hpp"
#include "Entity/CollidableEntity.hpp"

/// Events
#include "Events/Event.hpp"
#include "Events/CustomEvent.hpp"
#include "Events/BasicEvents/SceneTransitionEvent.hpp"


class Game;         // Forward Declaration of Game //

class RenderEngine; // Forward Declaration of RenderEngine //

class Transition;    // Forward Declaration of Transition //

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
    /// \brief returns a const reference to the Entity according to its name
    ///
    /// Returns nullptr if not found.
    ///
    /// \param name name of the entity
    ///
    /// \returns pointer to the entity, nullptr if not found
    ///
    /// \see Entity
    ////////////////////////////////////////////////////////////
    const Entity* getEntity(std::string name) const;
    ///////////////////////////////////////////////////////////
    /// \brief returns a const reference to the Entity according to its name
    ///
    /// If the entity cannot be casted to type T it will return nullptr.
    /// It also returns nullptr if there is no entity with this name.
    ///
    /// \tparam T type of the entity
    ///
    /// \param name name of the entity
    ///
    /// \returns pointer to the entity, can be nullptr
    ///
    /// \see Entity
    ////////////////////////////////////////////////////////////
    template <typename T>
    const T* getEntity(std::string name) const
    {
        // The function has to be there because of the template
        // If I wanted to put it in the cpp file,
        // I'd have to add one declaration for each type of entity
        // Which is not good for maintainability
        for (auto ent : entity_map_) {
            if (name == ent.first) {
                T* entity = dynamic_cast<T*>(ent.second);
                // returns nullptr if casting failed
                return entity;
            }
        }
        return nullptr;
    }

    ////////////////////////////////////////////////////////////
    /// \brief Extracts an entity from the scene
    ///
    /// This removes the entity from the map
    /// 
    /// \param name name of the entity
    ///
    /// \returns pointer to the entity, nullptr if not found
    ///
    /// \see T* extractEntity for templated version
    ////////////////////////////////////////////////////////////
    Entity* extractEntity(std::string name);

    ////////////////////////////////////////////////////////////
    /// \brief Extracts an entity of type T and named name from the scene
    ///
    /// Only extracts the entity if it can be casted to type T
    /// This removes the entity from the map
    /// 
    /// \tparam T type of the entity
    ///
    /// \param name name of the entity
    ///
    /// \returns pointer to the entity, nullptr if not found or cannot be casted
    ///
    /// \see Entity* extractEntity for non template version
    ///
    /// \todo test this function
    ////////////////////////////////////////////////////////////
    template <typename T>
    T* extractEntity(std::string name)
    {
        // The function has to be there because of the template
        // If I wanted to put it in the cpp file,
        // I'd have to add one declaration for each type of entity
        // Which is not good for maintainability
        Logger::log(SCENE, DEBUG, "EXTRACTING entity " + name);
        T* entity = nullptr;

        // search for the entity
        for (auto ent : entity_map_) {
            // Found the corresponding name
            if (name == ent.first)
                entity = dynamic_cast<T*>(ent.second);
        }

        if (entity == nullptr)
            Logger::log(SCENE, WARNING, "Extract : Entity " + name + " not found or cannot be casted");

        entity_map_.erase(name);
        return entity;
    }

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
    /// \brief Adds a transition to the scene
    ///
    /// The transition has to be fully constructed before adding it to the scene,
    /// this functions just takes a pointer to the transition.
    ///
    /// \param transition transition to add
    ////////////////////////////////////////////////////////////
    void addTransition(Transition* transition);

    ////////////////////////////////////////////////////////////
    /// \brief Adds an entity to the scene
    ///
    /// The entity has to be fully constructed before adding it to the scene,
    /// this functions just takes a pointer to the entity.
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

    ////////////////////////////////////////////////////////////
    /// \brief Gives a reference of all the drawables of the scene
    /// to the renderEngine so that they can be rendered
    ///
    /// Asssumes none of those Drawables are already attached.
    /// If they are, they will be rendered twice with the exact same position & everything.
    /// So beware !!!!!!
    ///
    /// for now it attaches :
    /// \li the EntitySpriteComponents
    ///
    /// Missing :
    /// \li Solid Tiles
    /// \li pure render assets (like decals or backgrounds)
    ///
    /// \param renderEngine Reference to the RenderEngine
    ////////////////////////////////////////////////////////////
    void attachDrawablesToRenderEngine(RenderEngine* renderEngine);

protected:
    ////////////////////////////////////////////////////////////
    /// Member Data
    ////////////////////////////////////////////////////////////
    Game* game_;                                                  ///< Reference to the game object
    std::string name_;                                            ///< Name of the current_scene
    std::unordered_map<std::string, Transition*> transition_map_; ///< Map of the Transitions
    std::unordered_map<std::string, Entity*> entity_map_;         ///< Map of the Entities
    sf::Vector2i origin_;                                         ///< Origin of the current scene in the global space
    sf::Vector2u size_;                                           ///< Size of the current scene

};

#endif