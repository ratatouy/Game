#ifndef COLLIDABLEENTITY_HPP
#define COLLIDABLEENTITY_HPP

////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
#include "Entity/Entity.hpp"
#include "Components/BasicComponents/ColliderComponent.hpp"

class CollidableEntity : public Entity
{
public:
    ////////////////////////////////////////////////////////////
    /// \brief Creates a CollidableEntity from a name, a transformable and a collider
    ///
    /// Creates a transformable then a colliderComponent and attach it to the transformable.
    ///
    /// \param name Name of the entity
    ////////////////////////////////////////////////////////////
    CollidableEntity(std::string name)
        : Entity(name) {collider_ = new ColliderComponent(transformable);}

    ////////////////////////////////////////////////////////////
    /// \brief Creates a CollidableEntity from a name, a transformable and a collider
    ///
    /// Creates a collider Component and attach it to the transformable.
    ///
    /// \param name Name of the entity
    ///
    /// \param transformable Transformable of the entity
    ////////////////////////////////////////////////////////////
    CollidableEntity(std::string name, sf::Transformable* transformable)
        : Entity(name, transformable) {collider_ = new ColliderComponent(transformable);}

    ////////////////////////////////////////////////////////////
    /// \brief Creates a CollidableEntity from a name, a transformable and a collider
    ///
    /// Creates a collider Component and attach it to the transformable.
    ///
    /// \param name Name of the entity
    ///
    /// \param transformable Transformable of the entity
    ///
    /// \param sprites EntitySpriteComponent of the entity
    ////////////////////////////////////////////////////////////
    CollidableEntity(std::string name, sf::Transformable* transformable, EntitySpriteComponent* sprites)
        : Entity(name, transformable, sprites) {collider_ = new ColliderComponent(transformable);}

    ////////////////////////////////////////////////////////////
    /// \brief Creates a CollidableEntity from a name, a transformable and a collider
    ///
    /// The colliderComponent will be attached to the transformable.
    ///
    /// \param name Name of the entity
    ///
    /// \param transformable Transformable of the entity
    ///
    /// \param collider Collider of the entity
    ////////////////////////////////////////////////////////////
    CollidableEntity(std::string name, sf::Transformable* transformable, ColliderComponent* collider)
        : Entity(name, transformable), collider_(collider) {collider_->setTransformable(transformable);}

    ////////////////////////////////////////////////////////////
    /// \brief destructor
    ////////////////////////////////////////////////////////////
    ~CollidableEntity() override {delete collider_;};

    ////////////////////////////////////////////////////////////
    /// \brief Returns a const-pointer to the colliderComponent
    ///
    /// \returns the const pointer to the ColliderComponent
    ////////////////////////////////////////////////////////////
    const ColliderComponent* getColliderComponent() const {return collider_;}

    ////////////////////////////////////////////////////////////
    /// \brief Set the colliderComponent of the CollidabelEntity
    ///
    /// \param collider collider component to set to the entity
    ////////////////////////////////////////////////////////////
    void setCollider(ColliderComponent* collider) {collider_ = collider;}

    ////////////////////////////////////////////////////////////
    /// \brief Checks collisions with another collidableEntity
    /// 
    /// \param other CollidableEntity to check collision with
    ///
    /// \returns true if there is a collision, false otherwise
    ////////////////////////////////////////////////////////////
    bool isCollidingWith(const CollidableEntity* other) const {return collider_->isCollidingWith(other->getColliderComponent());};

    ////////////////////////////////////////////////////////////
    /// \brief Process a Collision with an entity
    ///
    /// To be implemented this in the Derived Classes
    ///
    /// \param other entity it collided with
    ////////////////////////////////////////////////////////////
    virtual void processCollision(const CollidableEntity* other) = 0;

    ////////////////////////////////////////////////////////////
    /// \brief Updates the collidableComponent
    ////////////////////////////////////////////////////////////
    void update() override {}

protected:
    ColliderComponent* collider_;

};

#endif
