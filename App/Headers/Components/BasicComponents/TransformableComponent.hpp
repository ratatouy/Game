#ifndef TRANSFORMABLECOMPONENT_HPP
#define TRANSFORMABLECOMPONENT_HPP

#include <SFML/Graphics.hpp>

/** @class TransformableComponent @extends Component
 * 
 * @brief Component for Transformable objects, allows for those transformations :
 * - Translation 
 * - Rotation
 * - Scaling
 * 
 * @warning CPP file is empty bc it uses sfml's Transformable Class
 */
class TransformableComponent {
private:
    sf::Transformable transformable; // Global ID of The Component Type //


public:
    // Constructors //
    TransformableComponent() : transformable(sf::Transformable()) {};
    TransformableComponent(sf::Transformable transformable) : transformable(transformable) {};

    // Destructor //
    ~TransformableComponent() = default;


    // Getters & Setters //
    // Directly Calling sfml Transform methods //
    const sf::Vector2f getPosition() {return transformable.getPosition();};
    const float getRotation() {return transformable.getRotation();};
    const sf::Vector2f getScale() {return transformable.getScale();};
    const sf::Vector2f getOrigin() {return transformable.getOrigin();};

    void setPosition(sf::Vector2f position) {transformable.setPosition(position);};
    void setRotation(float angle) {transformable.setRotation(angle);};
    void setScale(sf::Vector2f scale) {transformable.setScale(scale);};

    void setOrigin(sf::Vector2f origin) {transformable.setOrigin(origin);};

    // Other sfml Transform methods //
    void rotate(float angle) {transformable.rotate(angle);};
};

#endif