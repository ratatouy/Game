#ifndef ENTITYSPRITECOMPONENT_HPP
#define ENTITYSPRITECOMPONENT_HPP

#include <SFML/Graphics.hpp>
#include "Components/BasicComponents/TransformableComponent.hpp"

/** @class EntitySpriteComponent @extends Component
 * 
 * @brief Component for Entity Sprites
 * 
 * @details made to support multiple sprites attached to a single entity
 */
class EntitySpriteComponent {
public:
    std::vector<sf::Sprite> sprites;                            // All the Sprites, their Transform is the sum of Local and Entity Transformables//
    std::vector<sf::Transformable> localSpriteTransformables;   // This is the list of Local Transforms //
    std::vector<sf::Texture*> textures;                         // Textures for the Sprites //
    TransformableComponent* entityTransformable;                // Reference to the Entity's Transformable Component //

    /** Constructor 
     * @param transformable Reference to the Entity's Transformable Component
     */
    EntitySpriteComponent(TransformableComponent* transformable) : entityTransformable(transformable) {};
    // Destructor //
    ~EntitySpriteComponent();


    /**
     * @param filepath Path to the texture
     */
    void AddSprite(std::string filepath);


    /** 
     * @param filepath Path to the texture
     * @param SrcRect Source Rectangle
    */
    void AddSprite(std::string filepath, sf::IntRect SrcRect);


    /**
     * @param spriteIndex Index of the sprite in the sprites vector
     */
    sf::Sprite* GetThisSprite(int spriteIndex)                      {return &sprites[spriteIndex];};


    /**
     * @param spriteIndex Index of the sprite in the sprites vector
     */
    sf::Transformable* GetThisSpriteLocalTransform(int spriteIndex) {return &localSpriteTransformables[spriteIndex];};


    // Directly Calling sfml Transform methods //
    void SetThisSpriteLocalPosition(int spriteIndex, sf::Vector2f position);
    void SetThisSpriteLocalRotation(int spriteIndex, float angle);
    void SetThisSpriteLocalScale(int spriteIndex, sf::Vector2f scale);
    void SetThisSpriteLocalTransform(int spriteIndex, sf::Vector2f position, float angle, sf::Vector2f scale);


    /**
     * @brief Updates the Entity Sprites
     * 
     * @details updates the position, rotation and scale of the sprites
     * Calculates the Sprite Transform using the Entity and Local Transforms
     */
    void update();


    /**
     * @brief Renders the Entity Sprites
     * 
     * @param window Pointer to the Render Window
     */
    void render(sf::RenderWindow* window);


private:
    /** 
     * @param filepath Path to the texture
    */
    sf::Texture* _LoadTexture(std::string filepath);
};

#endif