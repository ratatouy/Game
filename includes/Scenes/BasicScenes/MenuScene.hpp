#ifndef MENUSCENE_HPP
#define MENUSCENE_HPP

#include "Scenes/Scene.hpp"
#include <iostream>

class MenuScene : public Scene {
public:
    MenuScene() {};

    void processEventFunc(SceneTransitionEvent* event) override {
        std::cout << "MenuScene Processing SceneTransitionEvent" << std::endl;
    };
};

#endif