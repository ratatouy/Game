#include "logger.hpp"

int main()
{
    Logger::restart();

    Logger::log(ENTITY, DEBUG, "Hello world!");
    return 0;
}