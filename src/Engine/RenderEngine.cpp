#include "Engine/RenderEngine.hpp"
#include "Scenes/Scene.hpp"

#include <iostream>

bool RenderEngine::instantiated_ = false;


RenderEngine::RenderEngine(const char* title, int width, int height)
{
    if (instantiated_) {
        throw std::runtime_error("RenderEngine already instantiated");
    }
    instantiated_ = true;

    window_ = new sf::RenderWindow(sf::VideoMode(width, height), title);
}

RenderEngine::~RenderEngine()
{
    delete window_;
    instantiated_ = false;
}


void RenderEngine::addShaderObject(const char* filepath, sf::Shader::Type type)
{
    try 
    {
        int width = window_->getSize().x;
        int height = window_->getSize().y;

        sf::Texture texture;
        texture.create(width, height);
        sf::Sprite sprite(texture);

        sf::Shader shader;
        shader.loadFromFile(filepath, type);

        shader_objects_.push_back(std::make_pair(&sprite, &shader));

        shader.setUniform("resolution", sf::Vector2f(window_->getSize().x, window_->getSize().y));
    }
    catch (std::exception& err)
    {
        std::cout << "addShaderObject Error: " << err.what() << std::endl;
    }
}


// deltaTime HAS passed since last call
void RenderEngine::update(float deltaTime)
{
    std::cout << "Start RenderEngine::update" << std::endl;

    for (std::pair<sf::Sprite*, sf::Shader*> shader_object : shader_objects_)
    {
        std::cout << "o" << std::endl;
        std::cout << shader_object.second->isAvailable() << std::endl;

        shader_object.second->setUniform("time", deltaTime);
        std::cout << "o" << std::endl;

        sf::Vector2i mousePos = sf::Mouse::getPosition(*window_);
        shader_object.second->setUniform("mouse", (mousePos.x, mousePos.y));
    }

    std::cout << "End RenderEngine::update" << std::endl;
}


void RenderEngine::render()
{
    for (std::pair<sf::Sprite*, sf::Shader*> shader_object : shader_objects_)
    {
        window_->draw(*shader_object.first, shader_object.second);
    }
}