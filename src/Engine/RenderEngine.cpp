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
    delete currentScene_;

    for (auto iterator = drawables_.begin(); iterator != drawables_.end(); iterator++)
        delete iterator->second;

    for (auto iterator = shader_drawables_.begin(); iterator != shader_drawables_.end(); iterator++)
        delete iterator->second.first;

    drawables_.clear();
    shader_drawables_.clear();

    instantiated_ = false;
}



void RenderEngine::addDrawable(const char* name, sf::Drawable* drawable)
{
    try
    {
        drawables_.try_emplace(name);
        drawables_.find(name)->second = drawable;
    }
    catch (std::exception& err)
    {
        std::cout << "addShaderObject Error: " << err.what() << std::endl;
    }
}


void RenderEngine::addShaderDrawable(const char* name, sf::Drawable* drawable, const char* filepath, sf::Shader::Type type)
{
    try
    {
        shader_drawables_.try_emplace(name);

        shader_drawables_.find(name)->second.first = drawable;
        shader_drawables_.find(name)->second.second.loadFromFile(filepath, type);

        shader_drawables_.find(name)->second.second.setUniform("resolution", sf::Glsl::Vec2(window_->getSize().x, window_->getSize().y));
    }
    catch (std::exception& err)
    {
        std::cout << "addShaderObject Error: " << err.what() << std::endl;
    }
}


void RenderEngine::attachShaderToDrawable(const char* drawable_name, const char* filepath, sf::Shader::Type type)
{
    if (drawables_.find(drawable_name) == drawables_.end())
        throw(std::runtime_error("RenderEngine::attachShaderToDrawable : Tried adding Shader to non-existing drawable"));

    addShaderDrawable(drawable_name, drawables_.find(drawable_name)->second, filepath, type);

    drawables_.erase(drawable_name);
}

// deltaTime HAS passed since last call
void RenderEngine::update()
{
    updateShaders();
}



void RenderEngine::updateShaders()
{
    sf::Vector2i mousePos = sf::Mouse::getPosition(*window_);

    for (auto iterator = shader_drawables_.begin(); iterator != shader_drawables_.end(); iterator++)
    {
        if (!iterator->second.second.isAvailable())
            throw(std::runtime_error("Shader not available"));

        else
        {
            iterator->second.second.setUniform("time", total_clock_.getElapsedTime().asSeconds());

            iterator->second.second.setUniform("mouse", sf::Glsl::Vec2({(float)mousePos.x, (float)mousePos.y}));
        }
    }
}



void RenderEngine::render()
{
    // Render Shader Drawables
    for (auto iterator = shader_drawables_.begin(); iterator != shader_drawables_.end(); iterator++)
    {
        window_->draw(*iterator->second.first, &iterator->second.second);
    }

    // Render Shaderless Drawables
    for (auto iterator = drawables_.begin(); iterator != drawables_.end(); iterator++)
    {
        window_->draw(*iterator->second);
    }
}