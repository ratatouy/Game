#ifndef COLLIDERCOMPONENT_HPP
#define COLLIDERCOMPONENT_HPP

//////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
#include <SFML/Graphics.hpp>


////////////////////////////////////////////////////////////
/// \brief Adds a collision box to an object
///
/// It should be used to detect intersection between two collision boxes.
////////////////////////////////////////////////////////////
class ColliderComponent
{
public:
    ////////////////////////////////////////////////////////////
    /// \brief Creates a ColliderComponent from a sf::Transformable
    ///
    /// \param transformable the sf::Transformable to use
    ////////////////////////////////////////////////////////////
    ColliderComponent(sf::Transformable* transformable);

    ////////////////////////////////////////////////////////////
    /// \brief Creates a ColliderComponent from a sf::Transformable and a size
    ///
    /// \param transformable the sf::Transformable to use
    ///
    /// \param size the size of the collider
    ////////////////////////////////////////////////////////////
    ColliderComponent(sf::Transformable* transformable, sf::Vector2f size);
    
    ////////////////////////////////////////////////////////////
    /// \brief Creates a ColliderComponent from a sf::Transformable, a size and an offset
    ///
    /// \param transformable the sf::Transformable to use
    ///
    /// \param size the size of the collider
    ///
    /// \param offset the offset of the collider
    ////////////////////////////////////////////////////////////
    ColliderComponent(sf::Transformable* transformable, sf::Vector2f size, sf::Vector2f offset)
     : transformable_(transformable), size_(size), offset_(offset) {};
    
    ////////////////////////////////////////////////////////////
    /// \brief Default destructor
    ////////////////////////////////////////////////////////////
    ~ColliderComponent() = default;

    ////////////////////////////////////////////////////////////
    /// \brief Returns a const reference to the size of the collider
    ///
    /// \return The size
    ////////////////////////////////////////////////////////////
    const sf::Vector2f& getSize() const { return size_; }

    ///////////////////////////////////////////////////////////
    /// \brief Returns a const reference to the offset of the collider
    ///
    /// \return The offset
    ////////////////////////////////////////////////////////////
    const sf::Vector2f& getOffset() const { return offset_; }

    ////////////////////////////////////////////////////////////
    /// \brief Checks if there is a collision between two colliders
    ///
    /// \param other other ColliderComponent to check collisions with
    ///
    /// \return true if there is a collision, false otherwise
    ////////////////////////////////////////////////////////////
    bool hasCollided(ColliderComponent* other) const;

private:
    ////////////////////////////////////////////////////////////
    /// Member Data
    ////////////////////////////////////////////////////////////
        sf::Vector2f size_;                  ///< Size of the collider (it's a rectangle)
        sf::Vector2f offset_;                ///< Offset of the collider (it's a rectangle)
public: sf::Transformable* transformable_;   ///< Base transformable of the entity
};


#endif