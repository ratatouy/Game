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
/// Thus we have no need to calculate bounding boxes.
////////////////////////////////////////////////////////////
class ColliderComponent
{
public:
    ////////////////////////////////////////////////////////////
    /// \brief Creates a ColliderComponent from a sf::Transformable
    ///
    /// Size defaults to {1,1} and offset defaults to {0,0}
    ///
    /// \param transformable the sf::Transformable to use
    ////////////////////////////////////////////////////////////
    ColliderComponent(sf::Transformable* transformable);

    ////////////////////////////////////////////////////////////
    /// \brief Creates a ColliderComponent from a sf::Transformable and a size
    ///
    /// Offset defaults to {0,0}
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
    ///
    /// Doesn't destroy the Transformable.
    /// You don't have to worry if it's in an entity, as it's already done when destroying entity
    /// But in other cases (which you shouldn't do) it's up to you
    ////////////////////////////////////////////////////////////
    ~ColliderComponent() {};

    ////////////////////////////////////////////////////////////
    /// \brief Sets the transformable of the collider
    ///
    /// \param transformable the sf::Transformable to use
    ////////////////////////////////////////////////////////////
    void setTransformable(sf::Transformable* transformable) { transformable_ = transformable; }

    ////////////////////////////////////////////////////////////
    /// \brief Sets the size of the collider
    ///
    /// \param size the size of the collider
    ////////////////////////////////////////////////////////////
    void setSize(sf::Vector2f size) { size_ = size; }

    ////////////////////////////////////////////////////////////
    /// \brief Sets the offset of the collider
    ///
    /// \param offset the offset of the collider
    ////////////////////////////////////////////////////////////
    void setOffset(sf::Vector2f offset) { offset_ = offset; }

    ////////////////////////////////////////////////////////////
    /// \brief Returns a const pointer to the transformable of the collider
    ///
    /// \return The transformable
    ////////////////////////////////////////////////////////////
    const sf::Transformable* getTransformable() const { return transformable_; }

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
    bool isCollidingWith(const ColliderComponent* other) const;

private:
    ////////////////////////////////////////////////////////////
    /// Member Data
    ////////////////////////////////////////////////////////////
    sf::Vector2f size_;                  ///< Size of the collider (it's a rectangle)
    sf::Vector2f offset_;                ///< Offset of the collider from the entity's transformable position (it's a rectangle)
    sf::Transformable* transformable_;   ///< Base transformable of the entity
};


#endif