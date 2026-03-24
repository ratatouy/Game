#ifndef EVENTHANDLER_HPP
#define EVENTHANDLER_HPP

#include <queue>

#include "Events/Event.hpp"
#include "Events/BasicEvents/SceneTransitionEvent.hpp"
#include "Events/BasicEvents/SpawnEntityEvent.hpp"
#include "Events/CustomEvent.hpp"


class Game; // Forward Declaration of Game //

////////////////////////////////////////////////////////////
/// \brief Manages the event queue
/// 
/// This can only :
/// \li Add an event to the end of the queue
/// \li Return the current event
/// \li Process the current event
///
/// \warning Do not assign the same event to the queue twice, it will cause memory leaks
////////////////////////////////////////////////////////////
class EventHandler
{
public:
    ////////////////////////////////////////////////////////////
    /// \brief Default Constructor
    ///
    /// Will throw an error if the EventHandler is already instantiated
    ////////////////////////////////////////////////////////////
    EventHandler();

    EventHandler(const EventHandler&) = delete;             ///< deleted copy constructor to force singleton behavior
    EventHandler& operator=(const EventHandler&) = delete;  ///< deleted copy assignment to force singleton behavior

    ////////////////////////////////////////////////////////////
    /// \brief Destructor
    ////////////////////////////////////////////////////////////
    ~EventHandler();

    ////////////////////////////////////////////////////////////
    /// \brief Set the Game
    ///
    /// \param game Reference to the Game
    ////////////////////////////////////////////////////////////
    void setGame(Game* game);

    ////////////////////////////////////////////////////////////
    /// \brief Add an event to the queue
    ///
    /// \param event Reference to the event
    ////////////////////////////////////////////////////////////
    void addEvent(Event* event);

    ////////////////////////////////////////////////////////////
    /// \brief Process the next event
    ///
    /// This deletes the next event from the queue.
    ////////////////////////////////////////////////////////////
    void processEvent();

    ////////////////////////////////////////////////////////////
    /// \brief Return the current event
    ///
    /// This Method should not be used to process events, use processEvent instead.
    /// It should only be used to look at the next event, and modifying it will cause undefined behavior.
    ///
    /// \return Pointer to the current event
    ////////////////////////////////////////////////////////////
    Event* getCurrentEvent();

    ////////////////////////////////////////////////////////////
    /// \brief Check if the queue is empty
    ///
    /// \return True if the queue is empty
    ////////////////////////////////////////////////////////////
    bool isEmpty();


private:
    ////////////////////////////////////////////////////////////
    /// Member Data
    ////////////////////////////////////////////////////////////
    static bool instantiated_;     ///< Make sure the EventHandler is only instantiated once
    Game* game_;                   ///< Reference to the Game
    std::queue<Event*> eventQueue; ///< The queue of events

};


#endif