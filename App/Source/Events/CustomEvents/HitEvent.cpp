#include "Events/CustomEvents/HitEvent.hpp"


void* HitEvent::getData(){
    return &data;
}