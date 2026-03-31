#ifndef ENTITYSPRITECOMPONENT_HPP
#define ENTITYSPRITECOMPONENT_HPP

////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
#include <SFML/Graphics.hpp>


////////////////////////////////////////////////////////////
/// \brief Type used to store sprite data
///
/// It's a tuple containing :
/// \li The sprite
/// \li The local Transformable
/// \li The texture
////////////////////////////////////////////////////////////
using SpriteData = std::tuple<sf::Sprite,        ///< The sprite
                              sf::Transformable, ///< The local Transformable
                              sf::Texture*>;     ///< The texture


////////////////////////////////////////////////////////////
/// \brief Component to manage the sprites of an entity.
///
/// This stores a map of named sprites and their data (the sprite, the local transformable and the texture).
/// Only one EntitySpriteComponent is attached to each entity.
///
/// \details Created in order to support multiple sprites attached to a single entity.
////////////////////////////////////////////////////////////
class EntitySpriteComponent
{
public:
    ////////////////////////////////////////////////////////////
    /// \brief Lowest Constructor
    ///
    /// \param transformable Reference to the Entity's Transformable Component
    ////////////////////////////////////////////////////////////
    EntitySpriteComponent(sf::Transformable* transformable) : entityTransformable_(transformable), nb_sprites_(0) {};
    
    ////////////////////////////////////////////////////////////
    /// \brief Default Destructor
    ////////////////////////////////////////////////////////////
    ~EntitySpriteComponent();

    ////////////////////////////////////////////////////////////
    /// \brief Adds a sprite to the entity
    ///
    /// \param name Name of the sprite
    ///
    /// \param filepath Path to the texture
    ////////////////////////////////////////////////////////////
    void AddSprite(std::string name, const std::string& filepath);

    ////////////////////////////////////////////////////////////
    /// \brief Returns a const pointer to the map containing all the sprites
    ///
    /// \return const Pointer to the map
    ////////////////////////////////////////////////////////////
    const auto GetSpriteData() const {return &sprites_data_map_;}

    ////////////////////////////////////////////////////////////
    /// \brief Returns the number of sprites
    ///
    /// \return Number of sprites
    ////////////////////////////////////////////////////////////
    const int get_nb_sprites() const {return nb_sprites_;}

    ////////////////////////////////////////////////////////////
    /// \brief Returns a pointer to a sprite of Index "spriteIndex"
    ///
    /// \param spriteName name of the sprite in the sprites_data_map
    ///
    /// \returns const Pointer to the Requested Sprite
    ////////////////////////////////////////////////////////////
    const SpriteData* GetThisSpriteData(std::string spriteName)  {return &sprites_data_map_.find(spriteName)->second;}

    ////////////////////////////////////////////////////////////
    /// \brief Get the local Transformable of a sprite
    ///
    /// \param spriteName name of the sprite in the sprites_data_map
    ///
    /// \returns const Pointer to the Requested Transformable
    ////////////////////////////////////////////////////////////
    const sf::Sprite* GetThisSpriteLocalSprite(std::string spriteName) {return &std::get<0>(sprites_data_map_.find(spriteName)->second);}

    ////////////////////////////////////////////////////////////
    /// \brief Get the local Transformable of a sprite
    ///
    /// \param spriteName name of the sprite in the sprites_data_map
    ///
    /// \returns Pointer to the Requested Transformable
    ////////////////////////////////////////////////////////////
    sf::Transformable* GetThisSpriteLocalTransformable(std::string spriteName) {return &std::get<1>(sprites_data_map_.find(spriteName)->second);}

    ////////////////////////////////////////////////////////////
    /// \brief Get the local Transformable of a sprite
    ///
    /// \param spriteName name of the sprite in the sprites_data_map
    ///
    /// \returns const Pointer to the Requested Transformable
    ////////////////////////////////////////////////////////////
    const sf::Texture* GetThisSpriteLocalTexture(std::string spriteName) {return std::get<2>(sprites_data_map_.find(spriteName)->second);}

    ////////////////////////////////////////////////////////////
    /// \brief Set the local transform of a sprite
    ///
    /// \param spriteName name of the sprite in the sprites_data_map
    ///
    /// \param position New position
    ///
    /// \param angle New rotation angle
    ///
    /// \param scale New scale
    ////////////////////////////////////////////////////////////
    void SetThisSpriteLocalTransform(std::string spriteName, sf::Vector2f position, float angle, sf::Vector2f scale);

    ////////////////////////////////////////////////////////////
    /// \brief Updates all of the sprites
    ////////////////////////////////////////////////////////////
    void update();

private:
    ////////////////////////////////////////////////////////////
    /// \brief Loads a texture
    ///
    /// \param filepath Path to the texture
    ///
    /// \returns Pointer to the texture, nullptr if it can't be loaded
    ////////////////////////////////////////////////////////////
    sf::Texture* _LoadTexture(const std::string& filepath);

    ///////////////////////////////////////////////////////////
    /// Member Data
    ///////////////////////////////////////////////////////////
    int nb_sprites_;                                                    ///< Number of sprites
    std::unordered_map<std::string, SpriteData> sprites_data_map_;      ///< Map containing all the sprites ( \see SpriteData)
    sf::Transformable* entityTransformable_;                       ///< Reference to the Entity's Transformable Component
    
};

#endif