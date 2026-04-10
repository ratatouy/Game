#ifndef PLAYER_HPP
#define PLAYER_HPP

#include "Entity/CollidableEntity.hpp"
#include "Entity/Projectile/Projectile.hpp"

#include "Components/BasicComponents/EntitySpriteComponent.hpp"

#include "Events/CustomEvents/HitEvent.hpp"


////////////////////////////////////////////////////////////
/// \brief class for the Player Entity
///
/// The Player is the \b main \b character of the game
////////////////////////////////////////////////////////////
class Player : public CollidableEntity
{
public:
    ////////////////////////////////////////////////////////////
    /// \brief Lowest Constructor
    ///
    /// \param name Name of the Player
    ////////////////////////////////////////////////////////////
    Player(std::string name) : CollidableEntity(name) {};

    ////////////////////////////////////////////////////////////
    /// \brief Intermediate Transformable Constructor
    ///
    /// \param name Name of the Player
    ///
    /// \param transformable Pointer to the sf::Transformable to attach to the player
    ////////////////////////////////////////////////////////////
    Player(std::string name, sf::Transformable* transformable) : CollidableEntity(name, transformable) {};

    ////////////////////////////////////////////////////////////
    /// \brief Full Constructor
    ///
    /// \param name Name of the Player
    ///
    /// \param transformable Pointer to the sf::Transformable to attach to the player
    ///
    /// \param entitySprite Pointer to the EntitySpriteComponent to attache to the player
    ////////////////////////////////////////////////////////////
    Player(std::string name, sf::Transformable* transformable, EntitySpriteComponent* entitySprite) : CollidableEntity(name, transformable, entitySprite) {};

    ////////////////////////////////////////////////////////////
    /// \brief Full Constructor
    ///
    /// \param name Name of the Player
    ///
    /// \param transformable Pointer to the sf::Transformable to attach to the player
    ///
    /// \param entitySprite Pointer to the EntitySpriteComponent to attache to the player
    ///
    /// \param collider Pointer to the ColliderComponent to attach to the player
    ////////////////////////////////////////////////////////////
    Player(std::string name, sf::Transformable* transformable, EntitySpriteComponent* entitySprite, ColliderComponent* collider)
        : CollidableEntity(name, transformable, entitySprite) {collider_ = collider; collider_->setTransformable(transformable);};

    ////////////////////////////////////////////////////////////
    /// \brief Updates the Player
    ///
    /// \note Order of Updating is :
    /// \li IDK
    ////////////////////////////////////////////////////////////
    void update() override;

    void processCollision(const CollidableEntity* other) override;

    void attack();
};

#endif