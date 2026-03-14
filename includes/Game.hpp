#ifndef GAME_HPP
#define GAME_HPP

#include <map>

#include "Engine/RenderEngine.hpp"

#include "Events/Event.hpp"
#include "Events/CustomEvent.hpp"
#include "Events/BasicEvents/SceneTransitionEvent.hpp"
#include "Events/BasicEvents/SpawnEntityEvent.hpp"

#include "Entity/Entity.hpp"


class Scene;        // Forward Declaration of Scene        //

class EventHandler; // Forward Declaration of EventHandler //


struct SceneData
{

};



class Game
{
private:
    static bool instantiated_;

    Scene* active_scene_;
    EventHandler* eventHandler_;
    RenderEngine* renderEngine_;

    std::unordered_map<const char*, SceneData> scene_data_;
    /**< A Map of the data to use to load the Scenes */


public:
    Game();
    Game(const Game&) = delete;

    Game& operator=(const Game&) = delete;

    void setEventHandler(EventHandler* eventHandler) {eventHandler_ = eventHandler;}
    void setRenderEngine(RenderEngine* renderEngine) {renderEngine_ = renderEngine;}
    void setActiveScene(Scene* scene) {active_scene_ = scene;}

    EventHandler* getEventHandler() {return eventHandler_;}
    RenderEngine* getRenderEngine() {return renderEngine_;}
    Scene* getActiveScene() {return active_scene_;}


    void throwEvent(Event* event);


    void processEvent(SceneTransitionEvent* event);
    void processEventFunc(SceneTransitionEvent* event);
    void processEvent(SpawnEntityEvent* event);
    void processEventFunc(SpawnEntityEvent* event);
    void processEvent(CustomEvent* event);
    void processEventFunc(CustomEvent* event);


    void update();

    void render();


    /// @warning DON'T FORGET TO DELETE THIS FUNCTION, INSTEAD JUST USE LOADSCENE INSTEAD OR MAYBE NOT BUT I KNOW IT'S NOT A STABLE STRUCTURE SO AT LEAST THINK ABOUT IT AND REFORMAT
    void addEntity(Entity* entity);

};


#endif