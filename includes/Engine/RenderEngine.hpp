#ifndef RENDERENGINE_HPP
#define RENDERENGINE_HPP

////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
#include <array>
#include <string>
#include <vector>

#include <SFML/Graphics.hpp>

#include "Components/BasicComponents/EntitySpriteComponent.hpp"


class Game; // Forward Declaration of Game //

////////////////////////////////////////////////////////////
/// \brief Enum for the depth of the drawables
///
/// BACKGROUND is the farthest, FOREGROUND is the closest.
/// This means when rendering, BACKGROUND drawbables are drawn first, then DECALS, then GAMEPLAY, then FOREGROUND
////////////////////////////////////////////////////////////
enum Depth
{
    BACKGROUND = 0,
    DECALS = 1,
    GAMEPLAY = 2,
    FOREGROUND = 3
};

/// Number of depth levels (size of the enum), don't forget to update this if you add a new depth
const unsigned int DEPTH_SIZE = 4;

/// Shortcut type
using ESC = EntitySpriteComponent;
using ESCDepthList = std::array<std::unordered_map<std::string, ESC*>, DEPTH_SIZE>;

////////////////////////////////////////////////////////////
/// \brief Manages Shaders and the RenderWindow
///
/// The RenderEngine is in charge of rendering all the drawables and their associated Shaders.
/// It uses references to the drawables to render them.
/// When you want to create or delete an object,
/// you have to create/delete the object itself AND add/remove it from the RenderEngine.
/// That's why you should use the Game class to add or delete objects, as it also handles the RenderEngine.
///
/// For Shaders, the RenderEngine is in charge of creating and deleting them,
/// you can use addShaderDrawable() to create a Shader Drawable,
/// and attachShaderToDrawable() to add a Shader to a Drawable.
///
/// \warning A Drawable shouldn't be added to both drawables_ and shader_drawables_,
/// this will cause plenty of issues,
/// if you want to add a shader to a Drawable, please use attachShaderToDrawable() instead.
///
/// \note This object is a Singleton, use getInstance() to get a pointer to it's instance.
////////////////////////////////////////////////////////////
class RenderEngine
{
public:
    ////////////////////////////////////////////////////////////
    /// \brief Get the instance of the RenderEngine (Singleton), creates it if it doesn't exist
    ///
    /// \param game Reference to the Game
    ///
    /// \param title Title of the window
    ///
    /// \param width Width of the RenderWindow
    ///
    /// \param height Height of the RenderWindow
    ///
    /// \return Pointer to the RenderEngine
    ///
    /// \note The default window dimensions are 920x480 px/px
    ////////////////////////////////////////////////////////////
    static RenderEngine* getInstance(Game* game, std::string title = "Game", int width = 920, int height = 480);

    ////////////////////////////////////////////////////////////
    /// \brief Default Constructor
    ///
    /// \param game Reference to the Game
    ///
    /// \param title Title of the window
    ///
    /// \param width Width of the RenderWindow
    ///
    /// \param height Height of the RenderWindow
    ///
    /// \note the default width and height are 920x480
    ////////////////////////////////////////////////////////////
    RenderEngine(Game* game, std::string title = "Game", int width = 920, int height = 480);

    ////////////////////////////////////////////////////////////
    /// \brief Deleted copy constructor to force singleton behavior
    ////////////////////////////////////////////////////////////
    RenderEngine(const RenderEngine&) = delete;

    ////////////////////////////////////////////////////////////
    /// \brief Deleted copy assignment to force singleton behavior
    ////////////////////////////////////////////////////////////
    RenderEngine& operator=(const RenderEngine&) = delete;

    ////////////////////////////////////////////////////////////
    /// \brief Destructor
    ////////////////////////////////////////////////////////////
    ~RenderEngine();

    ////////////////////////////////////////////////////////////
    /// \brief Attaches the Scene to the RenderEngine
    ///
    /// \warning Deprecated (game is set in the constructor)
    ///
    /// \param game Reference to the Game
    ////////////////////////////////////////////////////////////
    void setGame(Game* game) {game_ = game;}

    ////////////////////////////////////////////////////////////
    /// \brief Returns a pointer to the RenderWindow
    ///
    /// \return Pointer to the RenderWindow
    ////////////////////////////////////////////////////////////
    const sf::RenderWindow* getWindow() const {return window_;}
    sf::RenderWindow* getWindow() {return window_;} ///< same thing as getWindow but non-const
    
    ////////////////////////////////////////////////////////////
    /// \brief Adds a Drawable with it's name to the RenderEngine
    ///
    /// \param name Name of the Entity possessing the ESC
    ///
    /// \param ESC Pointer to the ESC
    ///
    /// \param depth Depth of the ESC (defaults to GAMEPLAY)
    ///
    /// \see addShaderDrawable for ShaderDrawables
    ////////////////////////////////////////////////////////////
    void addESC(const std::string& name, ESC* ESC, Depth depth = GAMEPLAY);

    ////////////////////////////////////////////////////////////
    /// \brief Removes an ESC from the RenderEngine
    ///
    /// Removes the ESC from the map,
    /// It will just clear the pointer to the ESC, so the user is responsible for deleting the ESC itself.
    ///
    /// \param name Name of the Drawable
    ///
    /// \returns true if the ESC was found and removed, false otherwise
    ////////////////////////////////////////////////////////////
    bool removeESC(const std::string& name);

    ////////////////////////////////////////////////////////////
    /// \brief Removes all Drawables from the RenderEngine
    ///
    /// Doesn't delete the drawables, just empty the map,
    /// the user is responsible for deleting the drawables
    ////////////////////////////////////////////////////////////
    void clearAll();

    //////////////////////////////////////////////////////////// 
    /// \brief General Update Method
    ///
    /// Order of Operations :
    /// \li Updates the Shaders
    ////////////////////////////////////////////////////////////
    void update();

    ////////////////////////////////////////////////////////////
    /// \brief Update the shaders 
    ///
    /// \todo Update Shaders Depending on their args
    ////////////////////////////////////////////////////////////
    void updateShaders();

    ////////////////////////////////////////////////////////////
    /// \brief Renders the Drawables & ShaderDrawables
    ////////////////////////////////////////////////////////////
    void render();

private:
    ////////////////////////////////////////////////////////////
    /// Member Data
    ////////////////////////////////////////////////////////////
    static RenderEngine* instance_;               ///< Singleton
    static bool instantiated_;                    ///< Forces Singleton
    sf::RenderWindow* window_;                    ///< RenderWindow Object is stored here
    Game* game_;                                  ///< Reference to the Game
    ESCDepthList ESC_list_;   ///< see type def at the top of file "using..." \see ESCDepthList
public:    sf::Clock total_clock_;                ///< Clock to keep track of total time for Animated Shaders
};

#endif