#include <iostream>
#include <fstream>
#include "json.hpp"

#include "Loaders/sceneLoader.hpp"

int main()
{
    Scene* scene = LoadScene("Data/GameData/sceneData.json", "lvl10");
    return 0;
}
