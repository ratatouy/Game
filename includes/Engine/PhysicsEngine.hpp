#ifndef PHYSICENGINE_HPP
#define PHYSICENGINE_HPP

#include <SFML/System.hpp>

////////////////////////////////////////////////////////////
/// \brief The Physics Engine to Manage Physics (Physic Constants, Timers, etc.)
///
/// The Physics Engine is a singleton, use getInstance() to get a pointer to it's instance.
///
/// Stores physics constants and game timers
/// Those values can be accessed from anywhere with their associated getters.
///
/// The only non-getter method is tick(), which is used to tick the clock and wait until the next frame.
////////////////////////////////////////////////////////////

class PhysicEngine {
public:
    /// \brief Deleted Constructor
    PhysicEngine() = delete;

    ////////////////////////////////////////////////////////////
    /// \brief Initialize the PhysicEngine
    ///
    /// \param FPS Framerate of the game
    ////////////////////////////////////////////////////////////
    PhysicEngine(uint FPS);

    ////////////////////////////////////////////////////////////
    /// \brief Get the instance of the PhysicEngine (Singleton), creates it if it doesn't exist
    ///
    /// \param FPS Framerate of the game
    ////////////////////////////////////////////////////////////
    static PhysicEngine* getInstance(uint FPS = 60);

    ////////////////////////////////////////////////////////////
    /// \brief Ticks the PhysicEngine according to the framerate
    ///
    /// If the elapsed time is lower than the delta time,
    /// this method will "pause" the program for the remaining duration of this frame.
    /// In short, this method forces the game's frames to last >= delta time.
    ////////////////////////////////////////////////////////////
    void tick();

    ////////////////////////////////////////////////////////////
    /// \brief Get the current time
    ///
    /// returns the total elapsed time since the start of the current session.
    ///
    /// \return Current time in seconds
    ////////////////////////////////////////////////////////////
    float getSessionTime() {return session_runtime_clock.getElapsedTime().asSeconds();}


private:
    static PhysicEngine* instance_;    ///< Singleton
    static bool instantiated_;         ///< Singleton
    sf::Clock clock;                   ///< FPS Clock

    sf::Clock session_runtime_clock;   ///< Clock to track session runtime
    unsigned int FPS;                  ///< Frames per second
    unsigned int deltaTime;            ///< Time between two frames
};

#endif