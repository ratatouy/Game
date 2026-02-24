#ifndef HITEVENT_HPP
#define HITEVENT_HPP

#include "Events/CustomEvent.hpp"

struct HitData {
    const char* dealer;
    const char* target;
    int damage;
};

class HitEvent: public CustomEvent{
    public: HitData data;

    public: HitEvent(const char* dealer, const char* target, int damage) : data{dealer, target, damage} {};
    public: void* getData();
};

#endif