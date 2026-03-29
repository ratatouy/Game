#include "logger.hpp"

std::ofstream Logger::typeLogFile_ = std::ofstream();
std::ofstream Logger::logFile_ = std::ofstream();
const int Logger::logTypeSize = 9;
