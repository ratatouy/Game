#ifndef ENTITY_HPP
#define ENTITY_HPP

#include <SFML/Graphics.hpp>
#include "logger.hpp"

#include "Events/Event.hpp"
#include "Events/BasicEvents/SceneTransitionEvent.hpp"
#include "Events/CustomEvent.hpp"

#include "Components/BasicComponents/EntitySpriteComponent.hpp"


class Scene; // Forward Declaration of Scene

//////////////////////////////////////
/// \brief An Entity is an object that has an update and a render method
///
/// This class is abstract.
/// The sf::Transformable and EntitySpriteComponent are mandatory and public.
//////////////////////////////////////
class Entity {
public:
    ////////////////////////////////////////////////////////////
    /// \brief Default Constructor
    ///
    /// Deleted to prevent Entities from having no name.
    ////////////////////////////////////////////////////////////
    Entity() = delete;

    ////////////////////////////////////////////////////////////
    /// \brief Create an Entity with a name
    ///
    /// This automatically creates a sf::Transformable and an empty EntitySpriteComponent.
    ///
    /// \param name Name of the entity
    ////////////////////////////////////////////////////////////
    Entity(std::string name) : name_(name)
    {transformable = new sf::Transformable(); entitySprite = new EntitySpriteComponent(transformable);};


    ////////////////////////////////////////////////////////////
    /// \brief Create an entity from a name and a sf::Transformable
    ///
    /// The sf::Transformable has to be passed by reference because it will be attached to the entity.
    /// This automatically creates an EntitySpriteComponent.
    ///
    /// \param name Name of the entity
    ///
    /// \param transformable Pointer to the sf::Transformable to attach to the entity
    ////////////////////////////////////////////////////////////
    Entity(std::string name, sf::Transformable* tr) : name_(name), transformable(tr)
    {entitySprite = new EntitySpriteComponent(transformable);};


    ////////////////////////////////////////////////////////////
    /// \brief Create an entity from a name, a sf::Transformable and an EntitySpriteComponent
    ///
    /// The sf::Transformable and the EntitySpriteComponent
    /// have to be passed by reference because they will be attached to the entity.
    ///
    /// \param name Name of the entity
    ///
    /// \param transformable Pointer to the sf::Transformable to attach to the entity
    ///
    /// \param entitySprite Pointer to the EntitySpriteComponent to attach to the entity
    ////////////////////////////////////////////////////////////
    Entity(std::string name, sf::Transformable* tr, EntitySpriteComponent* eSpr)
    : name_(name), transformable(tr), entitySprite(eSpr) {}

    //////////////////////////////////////////////////////////
    /// \brief Default destructor
    //////////////////////////////////////////////////////////
    virtual ~Entity()
    {
        Logger::log(ENTITY, DEBUG, "DELETING entity");
        delete entitySprite;
        delete transformable;
    };

    ////////////////////////////////////////////////////////////
    /// \brief Set the current scene of the entity.
    ///
    /// \param scene Pointer to the scene
    ////////////////////////////////////////////////////////////
    void setScene(Scene* scene) {current_scene_ = scene;}


    ////////////////////////////////////////////////////////////
    /// \brief Set the name of the entity.
    ///
    /// \param name Name of the entity
    ////////////////////////////////////////////////////////////
    void setName(std::string name) {name_ = name;}

    ////////////////////////////////////////////////////////////
    /// \brief Get the name of the entity
    ///
    /// \returns Name of the entity
    ////////////////////////////////////////////////////////////
    const std::string& getName() const {return name_;}

    ////////////////////////////////////////////////////////////
    /// \brief Get the Transformable of the entity
    ///
    /// \returns Pointer to the Transformable
    ////////////////////////////////////////////////////////////
    const sf::Transformable* getTransformable() const {return transformable;}

    ////////////////////////////////////////////////////////////
    /// \brief Get the current scene of the entity
    ///
    /// \returns Pointer to the current scene
    ////////////////////////////////////////////////////////////
    const Scene* getCurrentScene() const {return current_scene_;}

    ////////////////////////////////////////////////////////////
    /// \brief Process a CustomEvent
    ///
    /// What it does depends on the CustomEvent type
    ///
    /// \param event Pointer to the CustomEvent
    ////////////////////////////////////////////////////////////
    virtual void processEvent(CustomEvent* event) {};

    ////////////////////////////////////////////////////////////
    /// \brief Update the entity
    ///
    /// "Update" might be a bit misleading as it doesn't fully update the entity.
    /// What I mean is it only updates what is possible to update without looking at other entities.
    /// Inter-entity update is managed in the scenes. \see Scene::update()
    ///
    /// \note Order of Updating should be :
    /// \li independant update (like move or process inputs)
    /// \li collisions         (check & process)
    /// \li update EntitySprite Component \see EntitySpriteComponent::update()
    ////////////////////////////////////////////////////////////
    virtual void update() = 0;

protected:
    ////////////////////////////////////////////////////////////
    /// Member Data
    ////////////////////////////////////////////////////////////
            Scene* current_scene_;                   ///< Pointer to the current scene
            std::string name_;                       ///< Name of the entity
public:     sf::Transformable* transformable;        ///< Pointer to the Transformable Component
public:     EntitySpriteComponent* entitySprite;     ///< Pointer to the EntitySprite Component

};


#endif