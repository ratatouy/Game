#ifndef ENTITYSPRITECOMPONENT_HPP
#define ENTITYSPRITECOMPONENT_HPP

////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
#include <SFML/Graphics.hpp>

#include <optional>


////////////////////////////////////////////////////////////
/// \brief Type used to store Sprite Data for a single sprite of an Entity
///
/// It's used in the EntitySpriteComponent.
///
/// It contains :
/// \li The sprite
/// \li The shader
/// \li The local Transformable
/// \li The texture
////////////////////////////////////////////////////////////
struct SpriteData {
    sf::Sprite sprite;                  ///< Sprite of the SpriteData
    std::optional<sf::Shader> shader;   ///< Shader of the SpriteData
    sf::Transformable transformable;    ///< Local Transformable of the SpriteData
    sf::Texture* texture;               ///< Texture of the SpriteData

    ////////////////////////////////////////////////////////////
    /// \brief Default Constructor
    ///
    /// I don't know why this is needed but apparently it is ¯\_(ツ)_/¯
    ////////////////////////////////////////////////////////////
    SpriteData() {
        sprite = sf::Sprite();
        shader = std::nullopt;
        transformable = sf::Transformable();
        texture = nullptr;
    }

    ////////////////////////////////////////////////////////////
    /// \brief Basic Constructor
    ///
    /// \param spr Sprite
    ///
    /// \param tr Local Transformable
    ///
    /// \param tex Texture
    ////////////////////////////////////////////////////////////
    SpriteData(sf::Sprite spr, sf::Transformable tr, sf::Texture* tex)
        : sprite(spr), transformable(tr), texture(tex), shader(std::nullopt) {}

    ////////////////////////////////////////////////////////////
    /// \brief Constructor with Shader
    ///
    /// \param spr Sprite
    ///
    /// \param tr Local Transformable
    ///
    /// \param tex Texture
    ///
    /// \param shader_path Path to the shader
    ///
    /// \param shader_type Type of the shader
    ////////////////////////////////////////////////////////////
    SpriteData(sf::Sprite spr, sf::Transformable tr, sf::Texture* tex, std::string shader_path, sf::Shader::Type shader_type)
        : sprite(spr), transformable(tr), texture(tex) { shader.emplace(); shader->loadFromFile(shader_path, shader_type); }
};

////////////////////////////////////////////////////////////
/// \brief Manages the sprites of an entity, there can be none to multiple sprites.
///
/// Each sprite has it's own name for easy access.
/// Each sprite has a SpriteData struct containing the sprite, the local transformable, the eventual shader and the texture.
/// As stated above, each sprite can have it's own shader, but it is not mandatory and will be ignored if not set.
/// Only one EntitySpriteComponent is attached to each entity.
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
    void addSprite(const std::string& spriteName, const std::string& filepath);

    ////////////////////////////////////////////////////////////
    /// \brief Attaches a shader to a sprite of the entity
    ///
    /// \param name Name of the sprite
    ///
    /// \param shaderPath Path to the shader
    ///
    /// \param shaderType Type of the shader
    ////////////////////////////////////////////////////////////
    void attachShaderToSprite(const std::string& spriteName, std::string shaderPath, sf::Shader::Type shaderType);

    ////////////////////////////////////////////////////////////
    /// \brief Returns a const pointer to the map containing all the sprites
    ///
    /// \return const Pointer to the map
    ////////////////////////////////////////////////////////////
    const auto GetSpriteData() const {return &sprites_data_map_;}
    auto GetSpriteData() {return &sprites_data_map_;} ///< Same as GetSpriteData() but non-const

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
    const SpriteData* GetThisSpriteData(std::string spriteName)  {return sprites_data_map_.find(spriteName)->second;}

    ////////////////////////////////////////////////////////////
    /// \brief Get the local Transformable of a sprite
    ///
    /// \param spriteName name of the sprite in the sprites_data_map
    ///
    /// \returns const Pointer to the Requested Transformable
    ////////////////////////////////////////////////////////////
    const sf::Sprite* GetThisSpriteLocalSprite(std::string spriteName) {return &sprites_data_map_.find(spriteName)->second->sprite;}

    ////////////////////////////////////////////////////////////
    /// \brief Get the local Transformable of a sprite
    ///
    /// \param spriteName name of the sprite in the sprites_data_map
    ///
    /// \returns Pointer to the Requested Transformable
    ////////////////////////////////////////////////////////////
    sf::Transformable* GetThisSpriteLocalTransformable(std::string spriteName) {return &sprites_data_map_.find(spriteName)->second->transformable;}

    ////////////////////////////////////////////////////////////
    /// \brief Get the local Transformable of a sprite
    ///
    /// \param spriteName name of the sprite in the sprites_data_map
    ///
    /// \returns const Pointer to the Requested Transformable
    ////////////////////////////////////////////////////////////
    const sf::Texture* GetThisSpriteLocalTexture(std::string spriteName) {return sprites_data_map_.find(spriteName)->second->texture;}

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
    int nb_sprites_;                                                  ///< Number of sprites
    std::unordered_map<std::string, SpriteData*> sprites_data_map_;   ///< Map containing all the sprites ( \see SpriteData)
    sf::Transformable* entityTransformable_;                          ///< Reference to the Entity's Transformable Component
    
};

#endif