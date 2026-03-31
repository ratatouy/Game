#ifndef GAME_HPP
#define GAME_HPP


////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
#include <map>
#include <iostream>

#include "Engine/RenderEngine.hpp"

#include "Events/Event.hpp"
#include "Events/CustomEvent.hpp"
#include "Events/BasicEvents/SceneTransitionEvent.hpp"
#include "Events/BasicEvents/SpawnEntityEvent.hpp"
#include "Entity/Entity.hpp"
#include "Loaders/sceneLoader.hpp"


class Scene;        // Forward Declaration of Scene        //

class EventHandler; // Forward Declaration of EventHandler //


////////////////////////////////////////////////////////////
/// \brief Main class of the game
///
/// The game is a collection of scenes, with only one active at a time.
/// It also is a singleton.
/// It's role is to bring together the RenderEngine, EventHandler and the active Scene.
///
/// \todo Maybe find a way to not have to read the json file each time a scene needs to be loaded.
////////////////////////////////////////////////////////////
class Game
{
public:
    ///////////////////////////////////////////////////////////
    /// \brief Get the instance of the Game (Singleton), creates it if it doesn't exist
    ///
    /// \return Reference to the Game
    ///////////////////////////////////////////////////////////
    static Game* getInstance();

    ////////////////////////////////////////////////////////////
    /// \brief Default Constructor
    ///
    /// Creates the EventHandler and the RenderEngine.
    /// Throws an error if the Game is already instantiated.
    ////////////////////////////////////////////////////////////
    Game();

    ////////////////////////////////////////////////////////////
    /// \brief Destructor
    ////////////////////////////////////////////////////////////
    ~Game();

    Game(const Game&) = delete;             ///< Delete copy constructor to force singleton behavior
    Game& operator=(const Game&) = delete;  ///< Delete copy assignment to force singleton behavior

    ////////////////////////////////////////////////////////////
    /// \brief Set the EventHandler
    ///
    /// \warning Deprecated (eventHandler is set in the constructor)
    ///
    /// \param eventHandler Reference to the EventHandler
    ////////////////////////////////////////////////////////////
    void setEventHandler(EventHandler* eventHandler) {eventHandler_ = eventHandler;}

    ////////////////////////////////////////////////////////////
    /// \brief Set the RenderEngine
    ///
    /// \warning Deprecated (renderEngine is set in the constructor)
    ///
    /// \param renderEngine Reference to the RenderEngine
    ////////////////////////////////////////////////////////////
    void setRenderEngine(RenderEngine* renderEngine) {renderEngine_ = renderEngine;}

    ////////////////////////////////////////////////////////////
    /// \brief Set the active Scene
    ///
    /// \param scene Reference to the Scene
    ////////////////////////////////////////////////////////////
    void setActiveScene(Scene* scene) {active_scene_ = scene;}

    ////////////////////////////////////////////////////////////
    /// \brief Get a reference to the EventHandler
    ///
    /// The EventHandler pointer is NOT a constant, so it can be used and modified
    ///
    /// \return Reference to the EventHandler
    ////////////////////////////////////////////////////////////
    const EventHandler* getEventHandler() const {return eventHandler_;}
    EventHandler* getEventHandler() {return eventHandler_;} ///< Returns a non-const pointer to the EventHandler

    ////////////////////////////////////////////////////////////
    /// \brief Get a reference to the RenderEngine
    ///
    /// This is the const version
    ///
    /// \return Reference to the RenderEngine
    ////////////////////////////////////////////////////////////
    const RenderEngine* getRenderEngine() const {return renderEngine_;}
    RenderEngine* getRenderEngine() {return renderEngine_;} ///< Returns a non-const pointer to the RenderEngine

    ////////////////////////////////////////////////////////////
    /// \brief Get a reference to the active Scene
    ///
    /// This is the const version
    ///
    /// \return Reference to the active Scene
    ////////////////////////////////////////////////////////////
    const Scene* getActiveScene() const {return active_scene_;}
    Scene* getActiveScene() {return active_scene_;} ///< Returns a non-const pointer to the active Scene

    void loadScene(const std::string& name);

    ////////////////////////////////////////////////////////////
    /// \brief Throw an event to the EventHandler
    ///
    /// This doesn't actually care about the type of the event,
    /// it just adds it to the queue of the EventHandler.
    ///
    /// \param event Reference to the event
    ////////////////////////////////////////////////////////////
    void throwEvent(std::unique_ptr<Event> event);

    ////////////////////////////////////////////////////////////
    /// \brief SceneTransitionEvent process distributor
    ///
    /// Distributes the SceneTransitionEvent to the objects that need it :
    /// \li The Scene (will unload it self)
    /// \li this ( \see processEventdistribute(SceneTransitionEvent* event) )
    /// It unloads the scene and \a then loads the new one.
    ///
    /// \param event Reference to the event
    ////////////////////////////////////////////////////////////
    void distributeEvent(SceneTransitionEvent* event);

    ////////////////////////////////////////////////////////////
    /// \brief Process a SceneTransitionEvent
    ///
    /// Loads a new Scene
    ///
    /// \param event Reference to the event
    ////////////////////////////////////////////////////////////
    void processEvent(SceneTransitionEvent* event);

    ////////////////////////////////////////////////////////////
    /// \brief SpawnEntityEvent process distributor
    ///
    /// Distributes the SpawnEntityEvent to the objects that need it :
    /// \li this
    /// \li The Scene
    ///
    /// \param event Reference to the event
    ////////////////////////////////////////////////////////////
    void distributeEvent(SpawnEntityEvent* event);

    ////////////////////////////////////////////////////////////
    /// \brief Process a SpawnEntityEvent
    ///
    /// \todo this is useless bc the event is processed by the scene. But I'm not sure so I'm putting it here.
    ///
    /// \param event Reference to the event
    ////////////////////////////////////////////////////////////
    void processEvent(SpawnEntityEvent* event);

    ////////////////////////////////////////////////////////////
    /// \brief CustomEvent process distributor
    ///
    /// We don't know what to do with the CustomEvent so we distribute it to all of the objects :
    /// \li The Scene
    ///
    /// \param event Reference to the event
    ////////////////////////////////////////////////////////////
    void distributeEvent(CustomEvent* event);

    ////////////////////////////////////////////////////////////
    /// \brief Process a CustomEvent
    ///
    /// What it does depends on the type of the CustomEvent
    ///
    /// \param event Reference to the event
    ////////////////////////////////////////////////////////////
    void processEvent(CustomEvent* event);


    ////////////////////////////////////////////////////////////
    /// \brief Update the Game
    ///
    /// Updates the active Scene.
    ////////////////////////////////////////////////////////////
    void update();

    ////////////////////////////////////////////////////////////
    /// \brief Render the Game
    ///
    /// Renders the active Scene.
    ////////////////////////////////////////////////////////////
    void render();


    ////////////////////////////////////////////////////////////
    /// \warning DON'T FORGET TO DELETE THIS TION, INSTEAD JUST USE LOADSCENE INSTEAD OR MAYBE NOT BUT I KNOW IT'S NOT A STABLE STRUCTURE SO AT LEAST THINK ABOUT IT AND REFORMAT
    /// \todo delete this
    ////////////////////////////////////////////////////////////
    void addEntity(Entity* entity);


private:
    ////////////////////////////////////////////////////////////
    /// Member Data
    ////////////////////////////////////////////////////////////
    static Game* instance_;                                 ///< instance
    static bool instantiated_;                              ///< Make sure the EventHandler is only instantiated once
    Scene* active_scene_;                                   ///< Reference to the active Scene
    EventHandler* eventHandler_;                            ///< Reference to the EventHandler
    RenderEngine* renderEngine_;                            ///< Reference to the RenderEngine

};


#endif