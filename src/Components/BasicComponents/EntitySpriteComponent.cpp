#include <iostream>

#include "logger.hpp"
#include "Components/BasicComponents/EntitySpriteComponent.hpp"
#include "Engine/PhysicsEngine.hpp"   // Needed to access timers when updating shaders


EntitySpriteComponent::~EntitySpriteComponent() {
    Logger::log(ENTITY_SPRITE, INFO, "DESTRUCTING EntitySpriteComponent");
    for (auto i = sprites_data_map_.begin(); i != sprites_data_map_.end(); i++)
    {
        delete i->second->texture;
    }
    // Doesn't delete the transformable
}


/** @details Implementation :
 * - Load the texture
 * - Create the sprite
 * - Set the sprite's position, rotation and scale to the entity's position, rotation and scale
 * - Add the sprite's local Transformable to the "localSpriteTransformables_" vector
 * - Add the sprite and texture to the "sprites_" and "textures_" vectors
 */
void EntitySpriteComponent::addSprite(const std::string& spriteName, const std::string& filepath)
{
    Logger::log(ENTITY_SPRITE, INFO, "ADDING sprite "+spriteName+" to an entity");

    try {
        sf::Texture* texture = _LoadTexture(filepath);
        if (!texture) return;
        
        sf::Sprite sprite;
        sprite.setTexture(*texture);

        sprite.setPosition(entityTransformable_->getPosition());
        sprite.setRotation(entityTransformable_->getRotation());
        sprite.setScale(entityTransformable_->getScale());

        sprites_data_map_[spriteName] = new SpriteData(sprite, sf::Transformable(), texture);

        nb_sprites_++;
    }
    catch (std::exception& e) {
        Logger::log(ENTITY_SPRITE, ERROR, "addSprite Error: " + (std::string)e.what());
    }
};


void EntitySpriteComponent::attachShaderToSprite(const std::string& spriteName, std::string shaderPath, sf::Shader::Type shaderType)
{
    Logger::log(ENTITY_SPRITE, INFO, "ATTACHING shader "+shaderPath+" to sprite "+spriteName);

    sprites_data_map_[spriteName]->shader.emplace();
    if (!sprites_data_map_[spriteName]->shader->loadFromFile(shaderPath, shaderType)) {
        Logger::log(ENTITY_SPRITE, ERROR, "Failed to load shader");
        throw(std::runtime_error("Failed to load shader"));
    }
}



void EntitySpriteComponent::SetThisSpriteLocalTransform(std::string spriteName, sf::Vector2f position, float angle, sf::Vector2f scale) {
    sf::Transformable* transformable = GetThisSpriteLocalTransformable(spriteName);
    transformable->setPosition(position);
    transformable->setRotation(angle);
    transformable->setScale(scale);
};


/** @details Implementation :
 * By summing the entity's position, rotation & origin with the sprite's local position and rotation
 * , Multiplying the entity's scale with the sprite's local scale
 * 
 * @note not optimal, updates everything, every frame
 */
void EntitySpriteComponent::update() {
    for (auto i = sprites_data_map_.begin(); i != sprites_data_map_.end(); i++)
    {
        sf::Sprite* sprite = &i->second->sprite;
        sf::Transformable* localTransfo = &i->second->transformable;

        sprite->setPosition(entityTransformable_->getPosition() + localTransfo->getPosition());
        sprite->setRotation(entityTransformable_->getRotation() + localTransfo->getRotation());
        sprite->setScale   (entityTransformable_->getScale().x  * localTransfo->getScale().x,
                            entityTransformable_->getScale().y  * localTransfo->getScale().y);
        sprite->setOrigin  (entityTransformable_->getOrigin()   + localTransfo->getOrigin());
    }
}



sf::Texture* EntitySpriteComponent::_LoadTexture(const std::string& filepath)
{
    Logger::log(ENTITY_SPRITE, INFO, "LOADING texture "+filepath);
    sf::Texture* texture = new sf::Texture();

    // handle load error
    if (!texture->loadFromFile(filepath)) {
        delete texture;
        throw(std::runtime_error("Failed to load texture"));
    }

    return texture;
};
