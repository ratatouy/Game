#ifndef PLAYER_HPP
#define PLAYER_HPP

#include "Entity/Entity.hpp"
#include "Entity/Projectile/Projectile.hpp"

#include "Components/BasicComponents/EntitySpriteComponent.hpp"

#include "Events/CustomEvents/HitEvent.hpp"


////////////////////////////////////////////////////////////
/// \brief class for the Player Entity
///
/// The Player is the \b main \b character of the game
////////////////////////////////////////////////////////////
class Player : public Entity
{
public:
    ////////////////////////////////////////////////////////////
    /// \brief Lowest Constructor
    ///
    /// \param name Name of the Player
    ////////////////////////////////////////////////////////////
    Player(const char* name) : Entity(name) {};

    ////////////////////////////////////////////////////////////
    /// \brief Intermediate Transformable Constructor
    ///
    /// \param name Name of the Player
    ///
    /// \param transformable Pointer to the sf::Transformable to attach to the player
    ////////////////////////////////////////////////////////////
    Player(const char* name, sf::Transformable* transformable) : Entity(name, transformable) {};

    ////////////////////////////////////////////////////////////
    /// \brief Full Constructor
    ///
    /// \param name Name of the Player
    ///
    /// \param transformable Pointer to the sf::Transformable to attach to the player
    ///
    /// \param entitySprite Pointer to the EntitySpriteComponent to attache to the player
    ////////////////////////////////////////////////////////////
    Player(const char* name, sf::Transformable* transformable, EntitySpriteComponent* entitySprite) : Entity(name, transformable, entitySprite) {};

    ////////////////////////////////////////////////////////////
    /// \brief Updates the Player
    ///
    /// \note Order of Updating is :
    /// \li IDK
    ////////////////////////////////////////////////////////////
    void update() override;

    void attack();
};

#endif