#ifndef LOGGER_HPP
#define LOGGER_HPP

#include <ctime>
#include <fstream>
#include <iostream>
#include <sstream>


enum LogLevel { DEBUG, INFO, WARNING, ERROR, CRITICAL };
///< Enum to represent log levels

enum LogType { MAIN, GAME, RENDER_ENGINE, EVENT_HANDLER, PARSER, SCENE, ENTITY, PLAYER, EVENT };
///< Enum to represent log types


////////////////////////////////////////////////////////////
/// \brief A logger to use to log information
////////////////////////////////////////////////////////////
class Logger {
public:
    /// Constructor unused bc everything is static (shhh dw it's clean code :clueless:)
    Logger() = delete;

    ////////////////////////////////////////////////////////////
    /// \brief Restarts the logger, erasing all logs
    ////////////////////////////////////////////////////////////
    static void restart()
    {
        for (unsigned int i = 0; i < logTypeSize; i++)
        {
            std::string filename = "Logs/" + _typeToString((LogType)i) + ".txt";
            typeLogFile_.open(filename);
            _closeFile(&typeLogFile_);
        }

        logFile_.open("Logs/general.txt");
        if (!logFile_.is_open()) {
            std::cerr << "Error opening log file." << std::endl;
        }
    }

    ////////////////////////////////////////////////////////////
    /// \brief Log a message to the console, general log file and a specific log file
    /// 
    /// \param type The log type
    ///
    /// \param level The log level
    ///
    /// \param message The message to log
    ////////////////////////////////////////////////////////////
    static void log(LogType type, LogLevel level, const std::string& message)
    {
        std::string filename = "Logs/" + _typeToString(type) + ".txt";
        _openFile(filename, &typeLogFile_);

        if (!logFile_.is_open()) {
            _openFile("Logs/general.txt", &logFile_);
        }

        // Get current timestamp
        std::time_t now = time(0);
        std::tm* timeinfo = localtime(&now);
        char timestamp[20];
        std::strftime(timestamp, sizeof(timestamp),
                 "%Y-%m-%d %H:%M:%S", timeinfo);

        // Create Type log entry
        std::ostringstream typedLogEntry;
        typedLogEntry << "[" << timestamp << "] "
                 << _levelToString(level) << ": " << message
                 << std::endl;
        
        // Create general log entry
        std::ostringstream generalLogEntry;
        generalLogEntry << "[" << timestamp << "] "
                 << _typeToString(type, true) << " - "
                 << _levelToString(level) << ": " << message
                 << std::endl;

        // Output to console
        std::cout << generalLogEntry.str();

        // Output to general log file
        if (logFile_.is_open()) {
            logFile_ << generalLogEntry.str();
            logFile_ .flush(); // Ensure immediate write to file
        }

        // Output to type specific log file
        if (typeLogFile_.is_open()) {
            typeLogFile_ << typedLogEntry.str();
            typeLogFile_ .flush(); // Ensure immediate write to file
        }

        _closeFile(&typeLogFile_);
    }
    

private:
    ////////////////////////////////////////////////////////////
    /// \brief Open a file without emptying it
    ///
    /// \param filename The name of the file to open
    ///
    /// \param stream The stream to open 
    ////////////////////////////////////////////////////////////
    static void _openFile(const std::string& filename, std::ofstream* stream)
    {
        stream->open(filename, std::ios::app);
        if (!stream->is_open()) {
            std::cerr << "Error opening log file." << std::endl;
        }
    }

    ////////////////////////////////////////////////////////////
    /// \brief Close a file
    ///
    /// \param stream The stream to close
    ////////////////////////////////////////////////////////////
    static void _closeFile(std::ofstream* stream) {stream->close();}

    ////////////////////////////////////////////////////////////
    /// \brief Converts log level to a string for output
    ///
    /// \param level The log level to convert
    ////////////////////////////////////////////////////////////
    static std::string _levelToString(LogLevel level)
    {
        switch (level) {
        case DEBUG:
            return "DEBUG   ";
        case INFO:
            return "INFO    ";
        case WARNING:
            return "WARNING ";
        case ERROR:
            return "ERROR   ";
        case CRITICAL:
            return "CRITICAL";
        default:
            return "UNKNOWN ";
        }
    }

    ////////////////////////////////////////////////////////////
    /// Converts log type to a string for output
    ///
    /// @param type The log type to convert
    ///
    /// @param with_space Whether to add a space after the type (to align the logs)
    ////////////////////////////////////////////////////////////
    static std::string _typeToString(LogType type, bool with_space = false)
    {
        switch (type) {
        case MAIN:
            return (with_space) ? "main   " : "main";
        case GAME:
            return (with_space) ? "game   " : "game";
        case RENDER_ENGINE:
            return (with_space) ? "render " : "render";
        case EVENT_HANDLER:
            return (with_space) ? "event  " : "event";
        case PARSER:
            return (with_space) ? "parser " : "parser";
        case SCENE:
            return (with_space) ? "scene  " : "scene";
        case ENTITY:
            return (with_space) ? "entity " : "entity";
        case PLAYER:
            return (with_space) ? "player " : "player";
        default:
            return (with_space) ? "unknown" : "unknown";
        }
    }


private:
    ////////////////////////////////////////////////////////////
    /// Member variables
    ////////////////////////////////////////////////////////////
    static std::ofstream typeLogFile_;   ///< Current stream for the typed log file
    static std::ofstream logFile_;       ///< Current stream for the general log file
    static const int logTypeSize;        ///< Number of log types (not including general)

};

#endif