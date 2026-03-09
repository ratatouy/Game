#ifndef RENDERENGINE_HPP
#define RENDERENGINE_HPP

#include <SFML/Graphics.hpp>

class Scene; // Forward Declaration of Scene //


/** Manages Shaders and the RenderWindow
 * 
 * @warning A Drawable shouldn't be added to both drawables_ and shader_drawables_, please use attachShaderToDrawable instead
 * 
 * @note Singleton
 */
class RenderEngine {

private:
    static bool instantiated_;          /**< Forces Singleton                   */

    sf::RenderWindow* window_;          /**< RenderWindow Object is stored here */
    Scene* currentScene_;               /**< Reference to the active Scene      */

    sf::Clock total_clock_;             /**< Clock to keep track of total time
                                             For Animated Shaders               */

    std::unordered_map<const char*, sf::Drawable*> drawables_;
    /**< List of all the Drawables that have no Shaders
     * 
     * Each drawable has a 'name', that isn't necessarily unique */

    std::unordered_map<const char*, std::pair<sf::Drawable*, sf::Shader>> shader_drawables_;
    /**< List of all the Drawables with Shaders
     * 
     * std::pair<Drawable*, Shader> associates each drawable to it's shader */


public:
    /** Only Constructor
     * 
     * @param title Title of the window
     * @param width Width of the RenderWindow
     * @param height Height of the RenderWindow
     * 
     * @note the default width and height are 920x480
     */
    RenderEngine(const char* title = "Game", int width = 920, int height = 480);
    RenderEngine(const RenderEngine&) = delete;

    RenderEngine& operator=(const RenderEngine&) = delete;

    ~RenderEngine();


    /** Attaches the Scene to the RenderEngine
     * 
     * @param scene Reference to the Scene
     */
    void setScene(Scene* scene) {currentScene_ = scene;}



    /** Window Getter (useless ?)
     * 
     * @return Pointer to the RenderWindow
     */
    sf::RenderWindow* getWindow() {return window_;}



    /** Adds a Drawable to the RenderEngine
     * 
     * @param name Name of the Drawable
     * @param drawable Pointer to the Drawable
     */
    void addDrawable(const char* name, sf::Drawable* drawable);
    


    /** Adds a ShaderDrawable to the RenderEngine
     * 
     * @param name Name of the Drawable
     * @param drawable Pointer to the Drawable
     * @param filepath Path to the Shader File
     * @param type Type of the Shader
     */
    void addShaderDrawable(const char* name, sf::Drawable* drawable, const char* filepath, sf::Shader::Type type);



    /** Attaches a Shader to a Drawable
     * 
     * @param drawable_name Name of the Drawable
     * @param filepath Path to the Shader File
     * @param type Type of the Shader
     */
    void attachShaderToDrawable(const char* drawable_name, const char* filepath, sf::Shader::Type type);



    /** General Update Method
     * 
     * Just updates the Shaders tbh
     */
    void update();


    
    /** Update the shaders 
     * 
     * @todo Update Shaders Depending on their args
    */
    void updateShaders();



    /** Renders the Drawables & ShaderDrawables */
    void render();
};

#endif