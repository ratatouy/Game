#ifndef EVENTA_HPP
#define EVENTA_HPP

#include "Events/Event.hpp"

class Scene;     // Forward declaration of Scene //


class SceneTransitionEvent : public Event {

private:
    const char* target;

public:
    SceneTransitionEvent(const char* target_name) : Event(), target(target_name) {};
};

#endif