#ifndef EVENTA_HPP
#define EVENTA_HPP

#include "Events/Event.hpp"

class Scene;     // Forward declaration of Scene //


class SceneTransitionEvent : public Event {

private:
    std::string target;

public:
    SceneTransitionEvent(std::string target_name) : Event(), target(target_name) {};

    std::string getTarget() const { return target; }
};

#endif