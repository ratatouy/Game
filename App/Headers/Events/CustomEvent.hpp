#ifndef CUSTOMEVENT_HPP
#define CUSTOMEVENT_HPP

#include "Events/Event.hpp"

/** @class EventA @extends Event
 * 
 * @brief Custom Event class for events, for user Custom Events
 */
class CustomEvent : public Event {
    public: void* getData() {return nullptr;};
};


#endif