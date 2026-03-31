#ifndef COLLIDABLEENTITY_HPP
#define COLLIDABLEENTITY_HPP


#include "Entity/Entity.hpp"
#include "Components/BasicComponents/ColliderComponent.hpp"

class CollidableEntity : public Entity
{
public:
    CollidableEntity(std::string name, ColliderComponent* collider) : Entity(name), collider_(collider) {}
    ~CollidableEntity() override;

    const ColliderComponent* getCollider() const {return collider_;}

    void setCollider(ColliderComponent* collider) {collider_ = collider;}

    void update() override {}

private:
    ColliderComponent* collider_;

};


#endif