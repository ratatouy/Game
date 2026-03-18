#include "logger.hpp"

std::ofstream Logger::typeLogFile_ = std::ofstream();
std::ofstream Logger::logFile_ = std::ofstream();
int Logger::logTypeSize = 7;
