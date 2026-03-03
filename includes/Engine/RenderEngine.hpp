#ifndef RENDERENGINE_HPP
#define RENDERENGINE_HPP

#include <SFML/Graphics.hpp>

#include "Scenes/Scene.hpp"

class Scene; // Forward Declaration of Scene //

class RenderEngine {

private:
    static bool instantiated_;
    sf::RenderWindow* window_;
    Scene* currentScene_;


public:
    RenderEngine(const char* title = "Game", int width = 920, int height = 480);
    RenderEngine(const RenderEngine&) = delete;

    RenderEngine& operator=(const RenderEngine&) = delete;

    ~RenderEngine();


    void setScene(Scene* scene) {currentScene_ = scene;}


    sf::RenderWindow* getWindow() {return window_;}

};

#endif