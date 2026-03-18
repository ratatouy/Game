#include "logger.hpp"

int main()
{
    Logger::restart();
    Logger::log(ENTITY, DEBUG, "This is a debug message");
    Logger::log(GAME, DEBUG, "This is a debug message");
    Logger::log(GAME, INFO, "This is an info message");
    Logger::log(GAME, WARNING, "This is a warning message");
    Logger::log(GAME, ERROR, "This is an error message");
    Logger::log(GAME, CRITICAL, "This is a critical message");

    return 0;
}