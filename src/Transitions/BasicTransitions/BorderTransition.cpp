#include "Transitions/BasicTransitions/BorderTransition.hpp"
#include "Scenes/Scene.hpp"


bool VerticalTransition::checkTransition(ColliderComponent* player_col) const
{
    sf::Vector2f player_pos  = player_col->transformable_->getPosition();
    sf::Vector2f player_size = player_col->getSize();
    sf::Vector2u scene_size  = scene_->getSize();
    sf::Vector2i scene_pos   = scene_->getOrigin();

    // if the player's coordinates do not satisfy the horizontal conditions
    // those conditions being independant of the orientation of the vertical transition
    if (player_pos.x > scene_pos.x + start_
        || player_pos.x + player_size.x < scene_pos.x + end_)
        return false;

    // if down check if the player is below the scene
    // if not (up) check if the player is above the scene
    return (down_) ?
        (player_pos.y + player_size.y > scene_pos.y + scene_size.y)
        :
        (player_pos.y < scene_pos.y);
}



bool HorizontalTransition::checkTransition(ColliderComponent* player_col) const
{
    sf::Vector2f player_pos  = player_col->transformable_->getPosition();
    sf::Vector2f player_size = player_col->getSize();
    sf::Vector2u scene_size  = scene_->getSize();
    sf::Vector2i scene_pos   = scene_->getOrigin();

    // if the player's coordinates do not satisfy the vertical conditions
    // those conditions being independant of the orientation of the horizontal transition
    if (player_pos.y > scene_pos.y + start_
        || player_pos.y + player_size.y < scene_pos.y + end_)
        return false;

    // if right check if the player is right of the scene
    // if not (left) check if the player is left of the scene
    return (right_) ?
        (player_pos.x + player_size.x > scene_pos.x + scene_size.x)
        :
        (player_pos.x < scene_pos.x);
}
