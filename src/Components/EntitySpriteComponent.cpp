#include <iostream>

#include "Components/BasicComponents/TransformableComponent.hpp"
#include "Components/BasicComponents/EntitySpriteComponent.hpp"


struct LocalTranform {
    sf::Vector2f position;
    float rotation;
    sf::Vector2f scale;
};


// Destructor //
EntitySpriteComponent::~EntitySpriteComponent() {
    for (auto t : textures) delete t;
    delete entityTransformable;
}


/**
 * @brief Adds a sprite to the entity
 * 
 * @param filepath Path to the texture
 * 
 * @details
 * - Load the texture
 * - Create the sprite
 * - Set the sprite's position, rotation and scale to the entity's position, rotation and scale
 * - Add the sprite and texture to the vectors
 */
void EntitySpriteComponent::AddSprite(std::string filepath)
{
    try {
        sf::Texture* texture = _LoadTexture(filepath);
        if (!texture) return;
        
        sf::Sprite sprite;
        sprite.setTexture(*texture);

        sprite.setPosition(entityTransformable->getPosition());
        sprite.setRotation(entityTransformable->getRotation());
        sprite.setScale(entityTransformable->getScale());

        localSpriteTransformables.push_back(sf::Transformable());

        sprites.push_back(sprite);
        textures.push_back(texture);
    }
    catch (std::exception& e) {
        std::cout << "Exception: " << e.what() << std::endl;
    }
};


/** 
 * @brief Adds a sprite to the entity with a source rectangle
 * 
 * @param filepath Path to the texture
 * @param SrcRect Source rectangle
 * 
 * @details
 * - Call AddSprite(filepath)
 * - Set the sprite's texture rectangle
 */
void EntitySpriteComponent::AddSprite(std::string filepath, sf::IntRect SrcRect)
{
    AddSprite(filepath);
    sprites.back().setTextureRect(SrcRect);
};



/**
 * @brief Local Transforms
 */
void EntitySpriteComponent::SetThisSpriteLocalPosition(int spriteIndex, sf::Vector2f position) { localSpriteTransformables[spriteIndex].setOrigin(-position); }
void EntitySpriteComponent::SetThisSpriteLocalRotation(int spriteIndex, float angle)           { localSpriteTransformables[spriteIndex].setRotation(angle); }
void EntitySpriteComponent::SetThisSpriteLocalScale(int spriteIndex, sf::Vector2f scale)       { localSpriteTransformables[spriteIndex].setScale(scale); }
void EntitySpriteComponent::SetThisSpriteLocalTransform(int spriteIndex, sf::Vector2f position, float angle, sf::Vector2f scale) {
    SetThisSpriteLocalPosition(spriteIndex, position);
    SetThisSpriteLocalRotation(spriteIndex, angle);
    SetThisSpriteLocalScale(spriteIndex, scale);
};

/**
 * @brief Updates the sprite's position, rotation and scale
 * 
 * @details By summing the entity's position, rotation & origin with the sprite's local position and rotation
 * , Multiplying the entity's scale with the sprite's local scale
 */
void EntitySpriteComponent::update() {
    for (int i = 0; i < sprites.size(); ++i)
    {
        sprites[i].setPosition(entityTransformable->getPosition()+localSpriteTransformables[i].getPosition());
        sprites[i].setRotation(entityTransformable->getRotation()+localSpriteTransformables[i].getRotation());
        sprites[i].setScale   (entityTransformable->getScale().x  * localSpriteTransformables[i].getScale().x,
                               entityTransformable->getScale().y  * localSpriteTransformables[i].getScale().y);
        sprites[i].setOrigin(entityTransformable->getOrigin()+localSpriteTransformables[i].getOrigin());
    }
}


/**
 * @brief Renders the sprite
 * 
 * @param window Pointer to the window
 * 
 * @details
 * For each sprite in the sprites vector :
 * - Draw the sprite on the window
 */
void EntitySpriteComponent::render(sf::RenderWindow* window)
{
    for (auto sprite : sprites)
        window->draw(sprite);
};


/**
 * @brief Loads a texture
 * 
 * @param name Path to the texture
 * 
 * @return sf::Texture* - pointer to the texture
 */
sf::Texture* EntitySpriteComponent::_LoadTexture(std::string name)
{
    sf::Texture* texture = new sf::Texture();
    if (!texture->loadFromFile(name)) {
        delete texture;
        return nullptr;
    }
    return texture;
};
