#ifndef TRANSFORMABLECOMPONENT_HPP
#define TRANSFORMABLECOMPONENT_HPP

#include <SFML/Graphics.hpp>

/** Class to manage transformations
 * 
 * @details Created in order to support more complex transformations
 * 
 * @note For now it supports :
 * - Translation
 * - Rotation
 * - Scaling
 */
class TransformableComponent {
private:
    sf::Transformable transformable_;
    sf::Vector2u size_;


public:
    /** Empty Constructor */
    TransformableComponent() : transformable_(sf::Transformable()) {};



    /** Highest Constructor
     * 
     * @param transformable Reference to the Entity's Transformable Component
     */
    TransformableComponent(sf::Transformable transformable) : transformable_(transformable) {};



    /** Default Destructor */
    ~TransformableComponent() = default;


    /** Position Getter
     * 
     * @return The position
    */
    const sf::Vector2f getPosition() {return transformable_.getPosition();};


    /** Rotation Getter
     * 
     * @return The rotation
     */
    const float getRotation() {return transformable_.getRotation();};


    /** Scale Getter
     * 
     * @return The scale
     */
    const sf::Vector2f getScale() {return transformable_.getScale();};


    /** Size Getter
     * 
     * @return The size
     */
    const sf::Vector2u getSize() {return size_;};


    /** Origin Getter
     * 
     * @return The origin
     */
    const sf::Vector2f getOrigin() {return transformable_.getOrigin();};

    

    /** Position Setter
     * 
     * @param position The new position
     */
    void setPosition(sf::Vector2f position) {transformable_.setPosition(position);};

    /** Rotation Setter
     * 
     * @param angle The new rotation angle
     */
    void setRotation(float angle) {transformable_.setRotation(angle);};


    /** Scale Setter
     * 
     * @param scale The new scale
     */
    void setScale(sf::Vector2f scale) {transformable_.setScale(scale);};


    /** Origin Setter
     * 
     * @param origin The new origin
     */
    void setOrigin(sf::Vector2f origin) {transformable_.setOrigin(origin);};



    /** Rotate the transformable clockwise
     * 
     * @param angle Angle to rotate
     */
    void rotate(float angle) {transformable_.rotate(angle);};


    /** Move the transformable
     * 
     * @param movement Movement to apply
     */
    void move(sf::Vector2f movement) {transformable_.move(movement);};
};

#endif