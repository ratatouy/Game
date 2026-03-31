#include <iostream>
#include <fstream>
#include "json.hpp"

#include "Loaders/sceneLoader.hpp"
#include "logger.hpp"

int Parser::_sceneTypeToInt(std::string type)
{
    if (type == "MENU")
        return 0;
    else if (type == "GAMEPLAY")
        return 1;
    else
        return -1;
}


Scene* Parser::LoadScene(std::string name, std::string filepath)
{
    Logger::log(PARSER, INFO, "PARSING scene \""+name+"\"");

    // Open the file
    std::ifstream f("Data/GameData/sceneData.json");

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
    int scene_type = _sceneTypeToInt(type);

    // Differ on sceneType
    switch (scene_type)
    {
        case 0:
            return new MenuScene(origin, size);
        case 1:
            return new GameplayScene(origin, size);
        default:
        {
            std::string error = "Scene : \"" + name + "\" not found";
            Logger::log(PARSER, ERROR, error);
            throw (std::runtime_error(error));
        }
    }
}
