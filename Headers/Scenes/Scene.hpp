#ifndef SCENE_HPP
#define SCENE_HPP

#include <unordered_map>
#include <memory>

#include <SFML/Graphics.hpp>

#include "Entity/Entity.hpp"
#include "Events/Event.hpp"
#include "Events/CustomEvent.hpp"
#include "Events/BasicEvents/EventA.hpp"

#include "Engine/RenderEngine.hpp"

class EventHandler; // Forward Declaration of EventHandler //

class RenderEngine; // Forward Declaration of RenderEngine //

class Scene {
private:
    RenderEngine* renderEngine_;

    EventHandler* eventHandler_;
    std::unordered_map<const char*, Entity*> entityMap_;

    
public:
    Scene();
    ~Scene();

    void setRenderEngine(RenderEngine* renderEngine) {renderEngine_ = renderEngine;}

    void setEventHandler(EventHandler* EventHandler) {eventHandler_ = EventHandler;}


    Entity* getEntity(const char* name);



    virtual void processEvent(EventA* event);
    virtual void processEventFunc(EventA* event) {};
    virtual void processEvent(CustomEvent* event);
    virtual void processEventFunc(CustomEvent* event) {};



    void throwEvent(Event* event);


    void addEntity(Entity* entity);



    virtual void update();


    void updateEntities();


    void renderEntities();

    
    void render();

private:
};

#endif