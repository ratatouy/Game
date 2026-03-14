#ifndef SPAWNENTITYEVENT_HPP
#define SPAWNENTITYEVENT_HPP

#include "Events/Event.hpp"
#include "Entity/Entity.hpp"

class SpawnEntityEvent : public Event
{
private:
    Entity* entity_;
public:
    SpawnEntityEvent(Entity* entity) {entity_ = entity;}
    Entity* getEntity() {return entity_;}
};


#endif
