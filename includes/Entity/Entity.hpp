#ifndef ENTITY_HPP
#define ENTITY_HPP

#include <SFML/Graphics.hpp>

#include "Events/Event.hpp"
#include "Events/BasicEvents/SceneTransitionEvent.hpp"
#include "Events/CustomEvent.hpp"

#include "Components/BasicComponents/TransformableComponent.hpp"
#include "Components/BasicComponents/EntitySpriteComponent.hpp"


class Scene; // Forward Declaration of Scene


//////////////////////////////////////
/// \class Entity
///
/// \brief An Entity is an object that has an update and a render method.
//////////////////////////////////////
class Entity {

protected:
    Scene* current_scene_; ///< Pointer to the current scene
    const char* name_;     ///< Name of the entity

    TransformableComponent* transformable_; ///< Pointer to the Transformable Component
    EntitySpriteComponent* entitySprite_;   ///< Pointer to the EntitySprite Component


public:
    Entity() = delete;


    /// \brief Lowest Constructor.
    /// \param name Name of the entity
    Entity(const char* name) : name_(name) {};


    /// \brief Intermediate Transformable Constructor.
    /// \param name Name of the entity
    /// \param transformable Pointer to the TransformableComponent to attach to the entity
    Entity(const char* name, TransformableComponent* transformable) : name_(name), transformable_(transformable) {}


    /// \brief Full Constructor.
    /// \param name Name of the entity
    /// \param transformable Pointer to the TransformableComponent to attach to the entity
    /// \param entitySprite Pointer to the EntitySpriteComponent to attach to the entity
    Entity(const char* name, TransformableComponent* transformable, EntitySpriteComponent* entitySprite)
    : name_(name), transformable_(transformable), entitySprite_(entitySprite) {}



    /// \brief Set the current scene of the entity.
    /// \param scene Pointer to the scene
    void setScene(Scene* scene) {current_scene_ = scene;}


    /// \brief Set the name of the entity.
    /// \param name Name of the entity
    void setName(const char* name) {name_ = name;}


    /** Set the Transformable Component of the entity
     * 
     * @param transformable Pointer to the Transformable Component
     */
    void setTransformable(TransformableComponent* transformable) {transformable_ = transformable;}


    /** Set the EntitySprite Component of the entity
     * 
     * @param entitySprite Pointer to the EntitySprite Component
     */
    void setEntitySprite(EntitySpriteComponent* entitySprite) {entitySprite_ = entitySprite;}



    /** Get the name of the entity
     * 
     * @returns Name of the entity
     */
    const char* getName() {return name_;}


    /** Get the current scene of the entity
     * 
     * @returns Pointer to the current scene
     */
    Scene* getCurrentScene() {return current_scene_;}


    /** Get the Transformable Component of the entity 
     * 
     * @returns Pointer to the Transformable Component
     */
    TransformableComponent* getTransformable() {return transformable_;}


    /** Get the EntitySprite Component of the entity 
     * 
     * @returns Pointer to the EntitySprite Component
     */
    EntitySpriteComponent* getEntitySprite() {return entitySprite_;}


    virtual void processEvent(SceneTransitionEvent* event) {};
    virtual void processEvent(CustomEvent* event) {};

    
    virtual void update() {};
    virtual void render(sf::RenderWindow* window) {};
};


#endif