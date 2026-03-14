#ifndef PLAYER_HPP
#define PLAYER_HPP

#include "Entity/Entity.hpp"
#include "Entity/Projectile/Projectile.hpp"

#include "Components/BasicComponents/EntitySpriteComponent.hpp"
#include "Components/BasicComponents/TransformableComponent.hpp"

#include "Events/CustomEvents/HitEvent.hpp"


/** class for the Player Entity */
class Player : public Entity {


public:
    /** Lowest Constructor
     * 
     * @param name Name of the Player
     */
    public: Player(const char* name) : Entity(name) {};


    /** Intermediate Transformable Constructor
     * 
     * @param name Name of the Player
     * @param transformable Pointer to the TransformableComponent to attach to the player
     */
    Player(const char* name, TransformableComponent* transformable) : Entity(name, transformable) {};


    /** Full Constructor
     * 
     * @param name Name of the Player
     * @param transformable Pointer to the TransformableComponent to attach to the player
     * @param entitySprite Pointer to the EntitySpriteComponent to attache to the player
     */
    Player(const char* name, TransformableComponent* transformable, EntitySpriteComponent* entitySprite) : Entity(name, transformable, entitySprite) {};
    


    /**
     * @brief Updates the Player
     * 
     * @note Order of Updating is :
     * - IDK
     */
    void update() override;


    void attack();
};

#endif