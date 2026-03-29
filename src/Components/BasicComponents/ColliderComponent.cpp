#include "Components/BasicComponents/ColliderComponent.hpp"


ColliderComponent::ColliderComponent(sf::Transformable* transformable) : transformable_(transformable)
{
    size_ = {1,1};
    offset_ = {0,0};
}

ColliderComponent::ColliderComponent(sf::Transformable* transformable, sf::Vector2f size) : transformable_(transformable), size_(size)
{
    offset_ = {0,0};
}

bool ColliderComponent::hasCollided(ColliderComponent* other) const
{
    sf::Vector2f m_pos = this->transformable_->getPosition()  + this->offset_;
    sf::Vector2f o_pos = other->transformable_->getPosition() + other->offset_;
    
    sf::Vector2f m_size = this->size_;
    sf::Vector2f o_size = other->size_;
    
    return m_pos.x < o_pos.x + o_size.x && m_pos.x + m_size.x > o_pos.x  // Horizontal
        && m_pos.y < o_pos.y + o_size.y && m_pos.y + m_size.y > o_pos.y; // Vertical
}