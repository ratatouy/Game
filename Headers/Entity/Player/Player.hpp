#ifndef PLAYER_HPP
#define PLAYER_HPP

#include "Entity/Entity.hpp"
#include "Entity/Projectile/Projectile.hpp"

#include "Components/BasicComponents/EntitySpriteComponent.hpp"
#include "Components/BasicComponents/TransformableComponent.hpp"

#include "Events/Event.hpp"
#include "Events/CustomEvent.hpp"
#include "Events/CustomEvents/HitEvent.hpp"


/**
 * @class Player
 */
class Player : public Entity {


protected:
    TransformableComponent* transformable_;
    EntitySpriteComponent* entitySprite_;


public:
    /**
     * @brief Lowest Constructor @memberof Player
     \param[in] name Name of the Player
     */
    public: Player(const char* name) : Entity(name) {};


    /**
     * @brief Intermediate Transformable Constructor @memberof Player
     * 
     * @param name Name of the Player
     * @param transformable Pointer to the TransformableComponent to attach to the player
     */
    Player(const char* name, TransformableComponent* transformable) : Entity(name), transformable_(transformable) {};


    /**
     * @brief Full Constructor
     * 
     * @param name Name of the Player
     * @param transformable Pointer to the TransformableComponent to attach to the player
     * @param entitySprite Pointer to the EntitySpriteComponent to attache to the player
     */
    Player(const char* name, TransformableComponent* transformable, EntitySpriteComponent* entitySprite) : Entity(name), transformable_(transformable), entitySprite_(entitySprite) {};
    

    /** @brief Transformable Setter
     * 
     * @param transformable Pointer to the TransformableComponent to attach to the player
    */
    void setTransformable(TransformableComponent* transformable) {this->transformable_ = transformable;}
    /** @brief EntitySprite Setter */
    void setEntitySprite(EntitySpriteComponent* entitySprite) {this->entitySprite_ = entitySprite;}


    /** @brief Transformable Getter */
    TransformableComponent* getTransformable() {return transformable_;}
    /** @brief EntitySprite Getter */
    EntitySpriteComponent* getEntitySprite() {return entitySprite_;}



    /**
     * @brief Updates the Player
     * 
     * @note Order of Updating is :
     * - IDK
     */
    void update() override;



    /**
     * @brief Renders the player
     * 
     * @param window Pointer to the RenderWindow
     */
    void render(sf::RenderWindow* window) override;



    void attack();
};

#endif