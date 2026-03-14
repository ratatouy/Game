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
    int nb_sprites_;


    std::unordered_map<const char*, std::tuple<
                                            sf::Sprite,
                                            sf::Transformable,
                                            sf::Texture*>>      sprites_data_map_;


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
    EntitySpriteComponent(TransformableComponent* transformable) : entityTransformable_(transformable), visible_(true), nb_sprites_(0) {};
    
    

    /** Default Destructor */
    ~EntitySpriteComponent();


    /** Adds a sprite to the entity
     * 
     * @param filepath Path to the texture
     */
    void AddSprite(const char* filepath);



    void AddSprite(const char* name, const char* filepath);
    auto GetSpriteData() {return &sprites_data_map_;}


    /** Adds a sprite to the entity with a source rectangle
     * 
     * @param filepath Path to the texture
     * @param SrcRect Source rectangle
     */
    void AddSprite(const char* filepath, sf::IntRect SrcRect);

    

    const std::vector<sf::Sprite> GetSprites() { return sprites_;}


    
    const int get_nb_sprites() {return nb_sprites_;}
     


    /** Returns a pointer to a sprite of Index "spriteIndex"
     * 
     * @param spriteIndex Index of the sprite in the sprites vector
     * 
     * @returns Pointer to the Requested Sprite
     */
    sf::Sprite* GetThisSprite(unsigned int spriteIndex)  {return &sprites_[spriteIndex];};



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