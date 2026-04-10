#ifndef EVENTA_HPP
#define EVENTA_HPP

#include "Events/Event.hpp"

class Scene;     // Forward declaration of Scene //

class Transition; // Forward declaration of Transition //

/*class SceneTransitionEvent : public Event {

private:
    std::string target;

public:
    SceneTransitionEvent(std::string target_name, std::string tr_type) : Event(), target(target_name) {};

    std::string getTarget() const { return target; }
};*/

class SceneTransitionEvent : public Event {

private:
    Transition* transition;

public:
    SceneTransitionEvent(Transition* tr) : Event(), transition(tr) {};

    const Transition* getTransition() const { return transition; }
};

#endif