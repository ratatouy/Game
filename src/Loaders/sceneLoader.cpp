#include <iostream>
#include <fstream>
#include "json.hpp"

#include "Loaders/sceneLoader.hpp"
#include "logger.hpp"


Scene* LoadScene(std::string name, std::string filepath)
{
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
        throw(std::runtime_error(error));
    }

    // Separates raw data
    auto orig = scene_data["origin"];
    auto siz = scene_data["size"];
    auto colliders = scene_data["colliders"];

    // Create needed components with the right types from the data
    sf::Vector2i origin = {orig[0], orig[1]};
    sf::Vector2u size = {siz[0], siz[1]};

    // Create the scene
    Scene* scene = new Scene(origin, size);

    return scene;
}
