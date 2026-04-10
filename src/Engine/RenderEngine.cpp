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

    for (int i = 0; i < DEPTH_SIZE; i++)
    {
        for (auto it : ESC_list_[i])
        {
            // delete the ESC
            delete it.second;
        }
    }

    instantiated_ = false;
}


void RenderEngine::addESC(const std::string& name, ESC* drawable, Depth depth)
{
    Logger::log(RENDER_ENGINE, INFO, "ADDING ESC " + (std::string)name);
   
    ESC_list_[depth][name] = drawable;
}


bool RenderEngine::removeESC(const std::string& name)
{
    for (int i = 0; i < DEPTH_SIZE; i++)
    {
        if (ESC_list_[i].find(name) != ESC_list_[i].end())
        {
            ESC_list_[i].erase(name);
            return true;
        }
    }
    return false;
}


void RenderEngine::clearAll()
{
    Logger::log(RENDER_ENGINE, INFO, "CLEAR all drawables");
    
    for (int i = 0; i < DEPTH_SIZE; i++)
    {
        ESC_list_[i].clear();
    }
}


// deltaTime HAS passed since last call
void RenderEngine::update()
{
    updateShaders();
}


// Not implemented yet
void RenderEngine::updateShaders()
{}


void RenderEngine::render()
{ 
    // Render using Depth order
    for (int i = 0; i < DEPTH_SIZE; i++)
    {
        // Render ESCs
        for (auto it : ESC_list_[i])
        {
            auto spriteDataLst = it.second->GetSpriteData();

            // Will render Sprites in order of insertion
            for (auto it2 = spriteDataLst->begin(); it2 != spriteDataLst->end(); it2++)
            {
                (it2->second->shader.has_value())
                ?   window_->draw(it2->second->sprite, &it2->second->shader.value())
                :   window_->draw(it2->second->sprite);
            }
        }
    }
}
