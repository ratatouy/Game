#ifndef EVENTHANDLER_HPP
#define EVENTHANDLER_HPP

#include <queue>

#include "Events/Event.hpp"
#include "Events/BasicEvents/SceneTransitionEvent.hpp"
#include "Events/BasicEvents/SpawnEntityEvent.hpp"
#include "Events/CustomEvent.hpp"


class Game; // Forward Declaration of Game //


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
private:
    static bool instantiated_;

    Game* game_;
    std::queue<Event*> eventQueue;


public:
    EventHandler();
    EventHandler(const EventHandler&) = delete;

    EventHandler& operator=(const EventHandler&) = delete;

    ~EventHandler();

    void setGame(Game* game);

    void addEvent(Event* event);
    void processEvent();
    Event* getCurrentEvent();
    bool isEmpty();

};


#endif