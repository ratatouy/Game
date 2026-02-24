#ifndef PLAYER_HPP
#define PLAYER_HPP

#include "Entity/Entity.hpp"
#include "Entity/Projectile/Projectile.hpp"

#include "Components/BasicComponents/EntitySpriteComponent.hpp"
#include "Components/BasicComponents/TransformableComponent.hpp"

#include "Events/Event.hpp"
#include "Events/CustomEvent.hpp"
#include "Events/CustomEvents/HitEvent.hpp"

class Player : public Entity {
public:
    Player(const char* name) : Entity(name) {};
    Player(const char* name, TransformableComponent* transform) : Entity(name), transform(transform) {};
    Player(const char* n, TransformableComponent* tr, EntitySpriteComponent* spr) : Entity(n), transform(tr), sprites(spr) {};
    
    void setTransformable(TransformableComponent* transform) {this->transform = transform;}
    void setEntitySprite(EntitySpriteComponent* sprites) {this->sprites = sprites;}

    TransformableComponent* getTransformable() {return transform;}
    EntitySpriteComponent* getEntitySprite() {return sprites;}

    void update() override;
    void render(sf::RenderWindow* window) override;

    void attack();

private:
    TransformableComponent* transform;
    EntitySpriteComponent* sprites;
};

#endif