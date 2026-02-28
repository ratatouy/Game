#include <iostream>

#include "Components/BasicComponents/TransformableComponent.hpp"
#include "Components/BasicComponents/EntitySpriteComponent.hpp"


EntitySpriteComponent::~EntitySpriteComponent() {
    for (auto t : textures_) delete t;
    delete entityTransformable_;
}


/** @details Implementation :
 * - Load the texture
 * - Create the sprite
 * - Set the sprite's position, rotation and scale to the entity's position, rotation and scale
 * - Add the sprite's local Transformable to the "localSpriteTransformables_" vector
 * - Add the sprite and texture to the "sprites_" and "textures_" vectors
 */
void EntitySpriteComponent::AddSprite(const char* filepath)
{
    try {
        sf::Texture* texture = _LoadTexture(filepath);
        if (!texture) return;
        
        sf::Sprite sprite;
        sprite.setTexture(*texture);

        sprite.setPosition(entityTransformable_->getPosition());
        sprite.setRotation(entityTransformable_->getRotation());
        sprite.setScale(entityTransformable_->getScale());

        localSpriteTransformables_.push_back(sf::Transformable());

        sprites_.push_back(sprite);
        textures_.push_back(texture);
    }
    catch (std::exception& e) {
        std::cout << "Exception: " << e.what() << std::endl;
    }
};



void EntitySpriteComponent::AddSprite(const char* filepath, sf::IntRect SrcRect)
{
    AddSprite(filepath);
    sprites_.back().setTextureRect(SrcRect);
};



void EntitySpriteComponent::SetThisSpriteLocalTransform(int spriteIndex, sf::Vector2f position, float angle, sf::Vector2f scale) {
    SetThisSpriteLocalPosition(spriteIndex, position);
    SetThisSpriteLocalRotation(spriteIndex, angle);
    SetThisSpriteLocalScale(spriteIndex, scale);
};


/** @details Implementation :
 * By summing the entity's position, rotation & origin with the sprite's local position and rotation
 * , Multiplying the entity's scale with the sprite's local scale
 */
void EntitySpriteComponent::update() {
    for (int i = 0; i < sprites_.size(); ++i)
    {
        sf::Transformable* transformable = &localSpriteTransformables_[i];

        sprites_[i].setPosition(entityTransformable_->getPosition() + transformable->getPosition());
        sprites_[i].setRotation(entityTransformable_->getRotation() + transformable->getRotation());
        sprites_[i].setScale   (entityTransformable_->getScale().x  * transformable->getScale().x,
                                entityTransformable_->getScale().y  * transformable->getScale().y);
        sprites_[i].setOrigin  (entityTransformable_->getOrigin()   + transformable->getOrigin());
    }
}



const void EntitySpriteComponent::render(sf::RenderWindow* window)
{
    if (visible_)
    {
        for (auto sprite : sprites_)
            window->draw(sprite);
    }
};



sf::Texture* EntitySpriteComponent::_LoadTexture(std::string name)
{
    sf::Texture* texture = new sf::Texture();
    if (!texture->loadFromFile(name)) {
        delete texture;
        return nullptr;
    }
    return texture;
};
