#ifndef EVENTHANDLER_HPP
#define EVENTHANDLER_HPP

#include <queue>

#include "Events/Event.hpp"
#include "Events/BasicEvents/EventA.hpp"
#include "Events/CustomEvent.hpp"

class Scene; // Forward Declaration of Scene //


/** @class EventHandler
 * @brief Manages the event queue
 * 
 * @details It uses a queue of Event pointers
 * 
 * @note Methods :
 * - Add any event to the end of the queue
 * - Return the current event
 * - Process the current event
 * 
 * @warning Do not assign the same event to the queue twice, it will cause memory leaks
 */
class EventHandler {
public:
    EventHandler();
    EventHandler(const EventHandler&) = delete;
    EventHandler& operator=(const EventHandler&) = delete;

    ~EventHandler();

    void setCurrentScene(Scene* scene);

    void addEvent(Event* event);
    void processEvent();
    Event* getCurrentEvent();
    bool isEmpty();

private:
    static bool instantiated_;

    Scene* currentScene;
    std::queue<Event*> eventQueue;
};


#endif