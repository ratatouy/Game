#ifndef ENTITYSPRITECOMPONENT_HPP
#define ENTITYSPRITECOMPONENT_HPP

#include <SFML/Graphics.hpp>
#include "Components/BasicComponents/TransformableComponent.hpp"

/**
 * @file EntitySpriteComponent.hpp
 */

/** 
 * @brief Component to manage the sprites of an entity.
 * 
 * @details Created in order to support multiple sprites attached to a single entity.
 */
class EntitySpriteComponent {

private:
    std::vector<sf::Sprite> sprites_;                            /**< All the Sprites. Their Transform is the sum of the Local and the Entity Transformables */
    std::vector<sf::Transformable> localSpriteTransformables_;   /**< List of each sprite's local Transformable                                              */
    std::vector<sf::Texture*> textures_;                         /**< List of textures for the Sprites                                                       */
    TransformableComponent* entityTransformable_;                /**< Reference to the Entity's Transformable Component                                      */
    bool visible_;                                               /**< Whether the sprite is visible or not                                                   */

    
public:
    /** Lowest Constructor
     * 
     * @param transformable Reference to the Entity's Transformable Component
     */
    EntitySpriteComponent(TransformableComponent* transformable) : entityTransformable_(transformable), visible_(true) {};
    
    

    /** Default Destructor */
    ~EntitySpriteComponent();


    /** Adds a sprite to the entity
     * 
     * @param filepath Path to the texture
     */
    void AddSprite(const char* filepath);



    /** Adds a sprite to the entity with a source rectangle
     * 
     * @param filepath Path to the texture
     * @param SrcRect Source rectangle
     */
    void AddSprite(const char* filepath, sf::IntRect SrcRect);



    /** Returns a pointer to a sprite of Index "spriteIndex"
     * 
     * @param spriteIndex Index of the sprite in the sprites vector
     * 
     * @returns Pointer to the Requested Sprite
     */
    const sf::Sprite* GetThisSprite(unsigned int spriteIndex)  {return &sprites_[spriteIndex];};



    /** Get the local Transformable of a sprite
     * 
     * @param spriteIndex Index of the sprite in the "sprites_" vector
     * 
     * @returns Pointer to the Requested Transformable
     */
    const sf::Transformable* GetThisSpriteLocalTransformable(int spriteIndex) {return &localSpriteTransformables_[spriteIndex];};


    /** Set the visibility of the sprite
     * 
     * @param visible New visibility
     */
    void setVisible(bool visible) {visible_ = visible;}


    /** Set the local position of a sprite
     * 
     * @param spriteIndex Index of the sprite in the "sprites_" vector
     * @param position New position
     */
    void SetThisSpriteLocalPosition(int spriteIndex, sf::Vector2f position) { localSpriteTransformables_[spriteIndex].setOrigin(-position); };



    /** Set the local rotation of a sprite
     * 
     * @param spriteIndex Index of the sprite in the "sprites_" vector
     * @param angle New rotation angle
     */
    void SetThisSpriteLocalRotation(int spriteIndex, float angle) { localSpriteTransformables_[spriteIndex].setRotation(angle); };



    /** Set the local scale of a sprite
     * 
     * @param spriteIndex Index of the sprite in the "sprites_" vector
     * @param scale New scale
     */
    void SetThisSpriteLocalScale(int spriteIndex, sf::Vector2f scale) { localSpriteTransformables_[spriteIndex].setScale(scale); };



    /** Set the local transform of a sprite
     * 
     * @param spriteIndex Index of the sprite in the "sprites_" vector
     * @param position New position
     * @param angle New rotation angle
     * @param scale New scale
     */
    void SetThisSpriteLocalTransform(int spriteIndex, sf::Vector2f position, float angle, sf::Vector2f scale);



    /** Updates all of the sprites */
    void update();



    /** Renders the entity's sprites
     * 
     * @param window Pointer to the Render Window
     */
    const void render(sf::RenderWindow* window);



private:
    /** Loads a texture
     * 
     * @param filepath Path to the texture
     * 
     * @returns Pointer to the texture, nullptr if it can't be loaded
    */
    sf::Texture* _LoadTexture(std::string filepath);
};

#endif