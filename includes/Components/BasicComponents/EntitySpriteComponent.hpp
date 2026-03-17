#ifndef ENTITYSPRITECOMPONENT_HPP
#define ENTITYSPRITECOMPONENT_HPP

#include <SFML/Graphics.hpp>
#include "Components/BasicComponents/TransformableComponent.hpp"

/**
 * @file EntitySpriteComponent.hpp
 */

using SpriteData = std::tuple<sf::Sprite,        /**< The sprite              */
                              sf::Transformable, /**< The local Transformable */
                              sf::Texture*>;     /**< The texture             */


/** 
 * @brief Component to manage the sprites of an entity.
 * 
 * @details Created in order to support multiple sprites attached to a single entity.
 */
class EntitySpriteComponent {

private:
    int nb_sprites_;

    std::unordered_map<std::string, SpriteData> sprites_data_map_;

    TransformableComponent* entityTransformable_;                /**< Reference to the Entity's Transformable Component */

    
public:
    /** Lowest Constructor
     * 
     * @param transformable Reference to the Entity's Transformable Component
     */
    EntitySpriteComponent(TransformableComponent* transformable) : entityTransformable_(transformable), nb_sprites_(0) {};
    
    

    /** Default Destructor */
    ~EntitySpriteComponent();


    /** Adds a sprite to the entity
     * 
     * @param name Name of the sprite
     * @param filepath Path to the texture
     */
    void AddSprite(std::string name, const char* filepath);
    auto GetSpriteData() {return &sprites_data_map_;}


    
    const int get_nb_sprites() {return nb_sprites_;}
     


    /** Returns a pointer to a sprite of Index "spriteIndex"
     * 
     * @param spriteName name of the sprite in the sprites_data_map
     * 
     * @returns const Pointer to the Requested Sprite
     */
    const SpriteData* GetThisSpriteData(std::string spriteName)  {return &sprites_data_map_.find(spriteName)->second;}


    /** Get the local Transformable of a sprite
     * 
     * @param spriteName name of the sprite in the sprites_data_map
     * 
     * @returns const Pointer to the Requested Transformable
     */
    const sf::Sprite* GetThisSpriteLocalSprite(std::string spriteName) {return &std::get<0>(sprites_data_map_.find(spriteName)->second);}

    /** Get the local Transformable of a sprite
     * 
     * @param spriteName name of the sprite in the sprites_data_map
     * 
     * @returns Pointer to the Requested Transformable
     */
    sf::Transformable* GetThisSpriteLocalTransformable(std::string spriteName) {return &std::get<1>(sprites_data_map_.find(spriteName)->second);}

    /** Get the local Transformable of a sprite
     * 
     * @param spriteName name of the sprite in the sprites_data_map
     * 
     * @returns const Pointer to the Requested Transformable
     */
    const sf::Texture* GetThisSpriteLocalTexture(std::string spriteName) {return std::get<2>(sprites_data_map_.find(spriteName)->second);}


    /** Set the local transform of a sprite
     * 
     * @param spriteName name of the sprite in the sprites_data_map
     * @param position New position
     * @param angle New rotation angle
     * @param scale New scale
     */
    void SetThisSpriteLocalTransform(std::string spriteName, sf::Vector2f position, float angle, sf::Vector2f scale);



    /** Updates all of the sprites */
    void update();


    
private:
    /** Loads a texture
     * 
     * @param filepath Path to the texture
     * 
     * @returns Pointer to the texture, nullptr if it can't be loaded
    */
    sf::Texture* _LoadTexture(const char* filepath);
};

#endif