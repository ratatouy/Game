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


/*void RenderEngine::addShaderObject(const char* filepath, sf::Drawable* drawable, sf::Shader::Type type)
{
    try 
    {
        int width = window_->getSize().x;
        int height = window_->getSize().y;

        sf::Shader* shader = new sf::Shader();
        shader->loadFromFile(filepath, type);

        shader_objects_.emplace(std::make_pair(drawable, shader));

        shader->setUniform("resolution", sf::Vector2f(window_->getSize().x, window_->getSize().y));
    }
    catch (std::exception& err)
    {
        std::cout << "addShaderObject Error: " << err.what() << std::endl;
    }
}*/

void RenderEngine::tick() {
    if (elapsed_clock_.getElapsedTime().asSeconds() < deltaTime)
    {
        sf::sleep(sf::seconds((deltaTime - elapsed_clock_.getElapsedTime().asMilliseconds())));
    }
    elapsed_clock_.restart();
}


// deltaTime HAS passed since last call
void RenderEngine::update()
{
    /* for (std::pair<sf::Sprite*, sf::Shader*> shader_object : shader_objects_)
    {
        std::cout << "o" << std::endl;
        std::cout << shader_object.second->isAvailable() << std::endl;

        shader_object.second->setUniform("time", deltaTime);
        std::cout << "o" << std::endl;

        sf::Vector2i mousePos = sf::Mouse::getPosition(*window_);
        shader_object.second->setUniform("mouse", (mousePos.x, mousePos.y));
    }*/

    my_shader.setUniform("time", total_clock_.getElapsedTime().asSeconds());

    sf::Vector2i mousePos = sf::Mouse::getPosition(*window_);
    my_shader.setUniform("mouse", sf::Glsl::Vec2(mousePos.x, mousePos.y));   
}


void RenderEngine::render()
{
    /*for (std::pair<sf::Sprite*, sf::Shader*> shader_object : shader_objects_)
    {
        window_->draw(*shader_object.first, shader_object.second);
    }*/

    window_->draw(my_shape, &my_shader);
}