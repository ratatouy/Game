#include <iostream>
#include <fstream>

#include "Loaders/sceneLoader.hpp"
#include "logger.hpp"


Scene* Parser::LoadScene(std::string name, std::string filepath)
{
    Logger::log(PARSER, INFO, "PARSING scene \""+name+"\"");

    // Open the file
    std::ifstream f(filepath);

    // Get all of the data
    nlohmann::json full_data = nlohmann::json::parse(f);

    // Get the scene that we want
    auto scene_data = full_data[name];

    // assert that the scene exists
    // and throw an error if it doesn't
    if (scene_data == nullptr)
    {
        std::string error = "Scene : \"" + name + "\" not found";
        Logger::log(PARSER, ERROR, error);
        throw (std::runtime_error(error));
    }

    // Separates scene base class common data
    auto orig = scene_data["origin"];
    auto siz = scene_data["size"];
    auto colliders = scene_data["colliders"];
    auto type = scene_data["type"];

    // Create needed components with the right types from the data
    sf::Vector2i origin = {orig[0], orig[1]};
    sf::Vector2u size = {siz[0], siz[1]};

    // Declare a scene* of any kind
    Scene* scene;

    // Differ on sceneType
    if (type == "MENU")
            scene = new MenuScene(origin, size);
    else if (type == "GAMEPLAY")
            scene = new GameplayScene(origin, size);
    else
    {
        std::string error = "Scene Type : \"" + name + "\" unknown";
        Logger::log(PARSER, ERROR, error);
        throw (std::runtime_error(error));
    }

    // Get all entities<
    std::vector<Entity*> entities = parseSceneEntities(name);

    // Add them to the scene (works on any kind of scene)
    for (auto entity : entities)
    {
        scene->addEntity(entity);
    }

    return scene;
}

/// \todo test with entitiless scenes
std::vector<Entity*> Parser::parseSceneEntities(std::string name, std::string filepath)
{
    // Open the file
    std::ifstream f(filepath);

    // Get all of the data
    nlohmann::json full_data = nlohmann::json::parse(f);

    // Get the scene that we want
    auto scene_entities_data = full_data[name];
    
    // Declare the vector
    std::vector<Entity*> entities = std::vector<Entity*>();

    for (auto it : scene_entities_data)
    {
        entities.push_back(parseEntity(it));
    }

    return entities;
}

Entity* Parser::parseEntity(nlohmann::json entity_iterator)
{
    auto type = entity_iterator["type"];
    auto name = entity_iterator["name"];
    auto sprites = entity_iterator["sprites"];
    auto transformable = entity_iterator["transformable"];
    
    std::string nm = name;
    sf::Transformable* tr = parseTransformable(transformable);
    EntitySpriteComponent* sp = parseEntitySpriteComponent(sprites, tr);

    if (type == "PLAYER")
        return new Player(nm, tr, sp);
    else if (type == "ENNEMY")
        return new Ennemy(nm, tr, sp);
    else
    {
        std::string error = "Entity type : \"" + nm + "\" unknown";
        Logger::log(PARSER, ERROR, error);
        throw (std::runtime_error(error));
    }
}

sf::Transformable* Parser::parseTransformable(nlohmann::json transformable_iterator)
{
    auto position = transformable_iterator["position"];
    auto scale = transformable_iterator["scale"];
    auto origin = transformable_iterator["origin"];
    float rotation = transformable_iterator["rotation"];

    sf::Vector2f pos = {position[0], position[1]};
    sf::Vector2f sc  = {scale[0],    scale[1]};
    sf::Vector2f ori = {origin[0],   origin[1]};

    sf::Transformable* tr = new sf::Transformable();
    tr->setPosition(pos);
    tr->setRotation(rotation);
    tr->setScale(sc);
    tr->setOrigin(ori);

    return tr;
}

EntitySpriteComponent* Parser::parseEntitySpriteComponent(nlohmann::json sprites_iterator, sf::Transformable* tr)
{
    EntitySpriteComponent* sp = new EntitySpriteComponent(tr);

    // add each sprites to the entity
    for (auto it : sprites_iterator)
    {
        std::string name = it["name"];
        std::string path = it["filepath"];
        sp->addSprite(name, path);
    }

    return sp;
}