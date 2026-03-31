#include "Engine/RenderEngine.hpp"
#include "Game.hpp"

#include "logger.hpp"

#include <iostream>


bool RenderEngine::instantiated_ = false;
RenderEngine* RenderEngine::instance_ = nullptr;


RenderEngine* RenderEngine::getInstance(Game* game, std::string title, int width, int height)
{
    if (instance_ == nullptr) {
        Logger::log(RENDER_ENGINE, INFO, "INSTANTIATE RenderEngine");
        instance_ = new RenderEngine(game, title, width, height);
        instantiated_ = true;
    }
    return instance_;
}

RenderEngine::RenderEngine(Game* game, std::string title, int width, int height)
{
    game_ = game;
    window_ = new sf::RenderWindow(sf::VideoMode(width, height), title);
}


RenderEngine::~RenderEngine()
{
    Logger::log(RENDER_ENGINE, INFO, "DELETING RenderEngine");

    delete window_;

    // delete drawables
    for (auto iterator = drawables_.begin(); iterator != drawables_.end(); iterator++)
        delete iterator->second;

    // delete shader drawables
    for (auto iterator = shader_drawables_.begin(); iterator != shader_drawables_.end(); iterator++)
        delete iterator->second.first;

    // clear maps
    drawables_.clear();
    shader_drawables_.clear();

    instantiated_ = false;
}



void RenderEngine::addDrawable(const std::string& name, sf::Drawable* drawable)
{
    Logger::log(RENDER_ENGINE, INFO, "ADDDING drawable " + (std::string)name);

    try
    {
        drawables_.try_emplace(name);
        drawables_.find(name)->second = drawable;
    }
    catch (std::exception& err)
    {
        Logger::log(RENDER_ENGINE, ERROR, "addDrawable Error: " + (std::string)err.what());
    }
}


void RenderEngine::addShaderDrawable(std::string name, sf::Drawable* drawable, std::string filepath, sf::Shader::Type type)
{
    Logger::log(RENDER_ENGINE, INFO, "ADDING shaderDrawable " + (std::string)name);

    try
    {
        shader_drawables_.try_emplace(name);

        shader_drawables_.find(name)->second.first = drawable;
        shader_drawables_.find(name)->second.second.loadFromFile(filepath, type);

        shader_drawables_.find(name)->second.second.setUniform("resolution", sf::Glsl::Vec2(window_->getSize().x, window_->getSize().y));
    }
    catch (std::exception& err)
    {
        Logger::log(RENDER_ENGINE, ERROR, "addShaderDrawable Error: " + (std::string)err.what());
    }
}


void RenderEngine::attachShaderToDrawable(std::string drawable_name, std::string filepath, sf::Shader::Type type)
{
    Logger::log(RENDER_ENGINE, INFO, "ATTACHING "+filepath+" shader to "+drawable_name);
    if (drawables_.find(drawable_name) == drawables_.end())
        throw(std::runtime_error("RenderEngine::attachShaderToDrawable : Tried adding Shader to non-existing drawable"));

    addShaderDrawable(drawable_name, drawables_.find(drawable_name)->second, filepath, type);

    drawables_.erase(drawable_name);
}

void RenderEngine::clearAll()
{
    Logger::log(RENDER_ENGINE, INFO, "CLEAR all drawables");
    drawables_.clear();
    shader_drawables_.clear();
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
        // std::cout << "Rendering Shader Drawable" << iterator->first << std::endl;
        window_->draw(*iterator->second.first, &iterator->second.second);
    }

    // Render Shaderless Drawables
    for (auto iterator = drawables_.begin(); iterator != drawables_.end(); iterator++)
    {   
        // std::cout << "Rendering Drawable " << iterator->first << std::endl;
        window_->draw(*iterator->second);
    }
}