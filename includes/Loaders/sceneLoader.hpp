#ifndef SCENELOADER_HPP
#define SCENELOADER_HPP

////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
#include "Components/BasicComponents/EntitySpriteComponent.hpp"

#include "Entity/Player/Player.hpp"
#include "Entity/Ennemies/Ennemy.hpp"

#include "Scenes/Scene.hpp"
#include "Scenes/BasicScenes/MenuScene.hpp"
#include "Scenes/BasicScenes/GameplayScene.hpp"

#include "json.hpp"

////////////////////////////////////////////////////////////
/// Manages Parsing data from json files to make them usable by the game
////////////////////////////////////////////////////////////
namespace Parser
{
    ////////////////////////////////////////////////////////////
    /// \brief Loads and builds a scene from a json file and returns it
    ///
    /// Loads :
    /// \li origin
    /// \li size
    ///
    /// Missing :
    /// \li colliders
    /// \li transitions
    /// \li entities
    ///
    /// \param name Name of the scene to load
    ///
    /// \param filepath Path to the json file (default : "Data/GameData/sceneData.json")
    ///
    /// \return Pointer to the loaded scene
    ///
    /// \see Scene
    ////////////////////////////////////////////////////////////
    Scene* LoadScene(std::string name, std::string filepath = "Data/GameData/sceneData.json");

    ////////////////////////////////////////////////////////////
    /// \brief Loads and builds all entities of a scene from a json file and returns them
    ///
    /// will return empty vector if the scene doesn't exist or doesn't have any data.
    ///
    /// \param name Name of the scene to load
    ///
    /// \param filepath Path to the json file (default : "Data/GameData/entityData.json")
    ///
    /// \return List of the loaded entities
    ///
    /// \see Entity
    ////////////////////////////////////////////////////////////
    std::vector<Entity*> parseSceneEntities(std::string name, std::string filepath = "Data/GameData/entityData.json");

    ///////////////////////////////////////////////////////////
    /// \brief Builds an entity from json data
    ///
    /// \param entity_data Data of the entity in json format
    ///
    /// \return Pointer to the loaded entity
    ///////////////////////////////////////////////////////////
    Entity* parseEntity(nlohmann::json entity_data);

    ///////////////////////////////////////////////////////////
    /// \brief Builds an sf::Transformable from json data
    ///
    /// \param transformable_iterator the json data
    ///
    /// \return the sf::Transformable
    ///////////////////////////////////////////////////////////
    sf::Transformable* parseTransformable(nlohmann::json transformable_iterator);

    ///////////////////////////////////////////////////////////
    /// \brief Builds an EntitySpriteComponent from json data and the sf::Transformable to attach
    ///
    /// \param sprites_iterator the json data
    ///
    /// \param tr reference to the sf::Transformable
    ///
    /// \return the EntitySpriteComponent
    ///////////////////////////////////////////////////////////
    EntitySpriteComponent* parseEntitySpriteComponent(nlohmann::json sprites_iterator, sf::Transformable* tr);

}

#endif