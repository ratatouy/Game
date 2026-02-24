#ifndef ENNEMY_HPP
#define ENNEMY_HPP

#include <iostream>

#include "Entity/Entity.hpp"
#include "Events/Event.hpp"
#include "Events/CustomEvents/HitEvent.hpp"

#include "Components/BasicComponents/TransformableComponent.hpp"
#include "Components/BasicComponents/EntitySpriteComponent.hpp"


class Ennemy : public Entity {
public:
    int health;

    Ennemy(const char* n, int h = 7) : Entity(n), health(h) {}
    Ennemy(const char* name, TransformableComponent* transform, int h = 7) : Entity(name), transform(transform), health(h) {};
    Ennemy(const char* name, TransformableComponent* transform, EntitySpriteComponent* sprites, int h = 7) : Entity(name), transform(transform), sprites(sprites), health(h) {};
    
    
    void setTransformable(TransformableComponent* transform) {this->transform = transform;}
    void setEntitySprite(EntitySpriteComponent* sprites) {this->sprites = sprites;}

    TransformableComponent* getTransformable() {return transform;}
    EntitySpriteComponent* getEntitySprite() {return sprites;}


    void update() override;
    void render(sf::RenderWindow* window) override;

    void processEvent(CustomEvent* event) override;

    void getHit(int damage);

private:
    TransformableComponent* transform;
    EntitySpriteComponent* sprites;
};

#endif