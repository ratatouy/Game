#ifndef RENDERENGINE_HPP
#define RENDERENGINE_HPP

////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
#include <SFML/Graphics.hpp>


class Game; // Forward Declaration of Scene //


////////////////////////////////////////////////////////////
/// \brief Manages Shaders and the RenderWindow
//
/// \warning A Drawable shouldn't be added to both drawables_ and shader_drawables_, please use attachShaderToDrawable instead
///
/// \note Singleton
////////////////////////////////////////////////////////////
class RenderEngine
{
public:
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
    sf::RenderWindow* getWindow() {return window_;} ///< \brief same but non-const
    

    ////////////////////////////////////////////////////////////
    /// \brief Returns a Drawable according to its name
    /// 
    /// Returns end() iterator if not found.
    ///
    /// \param name Name of the Drawable
    ///
    /// \return Pointer to the Drawable
    ///
    /// \see Game::addEntity for the name format of an EntitySpriteComponent's Drawable
    ////////////////////////////////////////////////////////////
    const sf::Drawable* getDrawable(std::string name) const {return drawables_.find(name)->second;}

    ////////////////////////////////////////////////////////////
    /// \brief Adds a Drawable with it's name to the RenderEngine
    ///
    /// \param name Name of the Drawable
    ///
    /// \param drawable Pointer to the Drawable
    ///
    /// \see addShaderDrawable for ShaderDrawables
    ////////////////////////////////////////////////////////////
    void addDrawable(const std::string& name, sf::Drawable* drawable);

    ////////////////////////////////////////////////////////////
    /// \brief Adds a ShaderDrawable by constructing the shader.
    ///
    /// We get a reference to the Drawable and a path to the Shader File.
    ///
    /// \param name Name of the Drawable
    ///
    /// \param drawable Pointer to the Drawable
    ///
    /// \param filepath Path to the Shader File
    ///
    /// \param type Type of the Shader
    ////////////////////////////////////////////////////////////
    void addShaderDrawable(std::string name, sf::Drawable* drawable, std::string filepath, sf::Shader::Type type);

    ////////////////////////////////////////////////////////////
    /// \brief Attaches a Shader to a Drawable
    ///
    /// \param drawable_name Name of the Drawable
    ///
    /// \param filepath Path to the Shader File
    ///
    /// \param type Type of the Shader
    ////////////////////////////////////////////////////////////
    void attachShaderToDrawable(std::string drawable_name, std::string filepath, sf::Shader::Type type);

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
    static bool instantiated_;          ///< Forces Singleton
    sf::RenderWindow* window_;          ///< RenderWindow Object is stored here
    Game* game_;                        ///< Reference to the Game
    sf::Clock total_clock_;             ///< Clock to keep track of total time for Animated Shaders
    std::unordered_map<std::string, sf::Drawable*> drawables_;
    ////////////////////////////////////////////////////////////
    ///< \brief List of all the Drawables that have no Shaders
    ///
    /// Each drawable has a 'name', that isn't necessarily unique
    /// for drawables from an EntitySpriteComponent, the name's format is "[entity's name]_[sprite's name]"
    ////////////////////////////////////////////////////////////
    std::unordered_map<std::string, std::pair<sf::Drawable*, sf::Shader>> shader_drawables_;
    ////////////////////////////////////////////////////////////
    ///< \brief List of all the Drawables with Shaders
    ///
    /// std::pair<Drawable*, Shader> associates each drawable to it's shader
    /// \see drawables_
    ////////////////////////////////////////////////////////////

};

#endif