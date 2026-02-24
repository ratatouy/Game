#ifndef EVENT_HPP
#define EVENT_HPP

static int EventCounter = 0;

/** @class Event
 * 
 * @brief Abstract class for all events
 */
class Event {
public:
    Event() {};
    virtual ~Event() {};
};

#endif