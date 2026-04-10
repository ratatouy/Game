#include "logger.hpp"

// Initialize file streams
std::ofstream Logger::typeLogFile_ = std::ofstream();
std::ofstream Logger::logFile_ = std::ofstream();

// Initialize number of log types
const int Logger::logTypeSize = 11;

// Is it muted ?
const bool Logger::muted = false;

// Set muted types here
const std::vector<bool> Logger::typeLogOnlyTypes =
/*{0, // main
 0, // game
 0, // render
 0, // event
 0, // parser
 0, // scene
 0, // entity
 0, // sprite
 0, // transition
 0, // player
 0  // unknown
};*/
{false, // main
 false, // game
 false, // render
 false, // parser
 false, // scene
 false, // entity
 true, // sprite
 false, // player
 true, // event
 false, // transition
 false  // unknown
};
