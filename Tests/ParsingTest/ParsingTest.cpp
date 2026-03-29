#include <iostream>
#include <fstream>
#include "json.hpp"

#include "Loaders/sceneLoader.hpp"
#include "logger.hpp"

int main()
{
    Logger::restart();
    Scene* scene = LoadScene("lvl1");
    return 0;
}
