#ifndef DELETEENTITYEVENT_HPP
#define DELETEENTITYEVENT_HPP

#include "Events/Event.hpp"
#include "Entity/Entity.hpp"

class DeleteEntityEvent : public Event
{
private:
    std::string name_;

public:
    DeleteEntityEvent(const std::string& name) {name_ = name;}
    const std::string& getName() const {return name_;}
};


#endif
