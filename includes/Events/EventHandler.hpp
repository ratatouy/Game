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
/// You have to move the ownership of the events to the EventHandler with std::move
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
    /// \brief Get the EventHandler instance, creates it if it doesn't exist
    ///
    /// \param game Reference to the Game
    ///
    /// \return Pointer to the EventHandler
    ////////////////////////////////////////////////////////////
    static EventHandler* getInstance(Game* game);

    ////////////////////////////////////////////////////////////
    /// \brief Default Constructor
    ///
    /// Will throw an error if the EventHandler is already instantiated.
    ///
    /// \param game Reference to the Game
    ////////////////////////////////////////////////////////////
    EventHandler(Game* game);

    EventHandler(const EventHandler&) = delete;             ///< deleted copy constructor to force singleton behavior
    EventHandler& operator=(const EventHandler&) = delete;  ///< deleted copy assignment to force singleton behavior

    ////////////////////////////////////////////////////////////
    /// \brief Destructor
    ////////////////////////////////////////////////////////////
    ~EventHandler();

    ////////////////////////////////////////////////////////////
    /// \brief Set the Game
    ///
    /// \warning Deprecated (game is set in the constructor)
    ///
    /// \param game Reference to the Game
    ////////////////////////////////////////////////////////////
    void setGame(Game* game);

    ////////////////////////////////////////////////////////////
    /// \brief Add an event to the queue
    ///
    /// \param event Reference to the event
    ////////////////////////////////////////////////////////////
    void addEvent(std::unique_ptr<Event> event);

    ////////////////////////////////////////////////////////////
    /// \brief Process the next event
    ///
    /// This deletes the next event from the queue.
    ////////////////////////////////////////////////////////////
    void processEvent();

    ////////////////////////////////////////////////////////////
    /// \brief Check if the queue is empty
    ///
    /// \return True if the queue is empty
    ////////////////////////////////////////////////////////////
    bool isEmpty();


private:
    ////////////////////////////////////////////////////////////
    /// \brief Return the next event to process and remove it from the queue
    ///
    /// \return Pointer to the current event
    ////////////////////////////////////////////////////////////
    std::unique_ptr<Event> _getEventToProcess();

    ////////////////////////////////////////////////////////////
    /// Member Data
    ////////////////////////////////////////////////////////////
    static EventHandler* instance_;                  ///< Singleton
    static bool instantiated_;                       ///< Make sure the EventHandler is only instantiated once
    Game* game_;                                     ///< Reference to the Game
    std::queue<std::unique_ptr<Event>> eventQueue;   ///< The queue of events

};


#endif