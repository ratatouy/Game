#include "Entity/Entity.hpp"
#include "Scenes/Scene.hpp"


void Entity::setScene(Scene* scene) {current_scene = scene;}

void Entity::processEvent(EventA* event) {};
void Entity::processEvent(CustomEvent* event) {};

void Entity::update() {}

void Entity::render(sf::RenderWindow* window) {}
