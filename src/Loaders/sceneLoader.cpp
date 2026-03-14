#include <iostream>
#include <fstream>
#include "json.hpp"


#include "Loaders/sceneLoader.hpp"


Scene* LoadScene(const char* filepath)
{
    Scene* scene = new Scene();

    std::ifstream f("Data/GameData/sceneData.json");
    nlohmann::json data = nlohmann::json::parse(f);

    for (auto it = data.begin(); it != data.end(); it++)
    {
        std::cout << it.key() << std::endl;

        /*std::cout << "| colliders : " << std::endl;

        auto val=it.value()["colliders"];
        for (int i = 0; i<4; i++)
        {
            std::cout <<"| | "<< val[i] << std::endl;
        }*/

        for (auto it2 = it.value().begin(); it2 != it.value().end(); it2++)
        {
            if (it2.key() == "colliders")
            {
                continue;
            }

            std::cout << "| " << it2.key() << " : " << it2.value()<< std::endl;
        }
    }

    return scene;
}
