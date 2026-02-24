#include <SFML/Graphics.hpp>

#include <iostream>

#include "Components/EntitySpriteComponent.hpp"


int main() {

    sf::Event event;
    sf::RenderWindow* window = new sf::RenderWindow(sf::VideoMode(920, 480), "Hello World");

    
    TransformableComponent* raptorTransformable = new TransformableComponent();
    raptorTransformable->setPosition({300, 200});


    EntitySpriteComponent* raptorSprite = new EntitySpriteComponent(raptorTransformable);
    raptorSprite->AddSprite("Sprites/raptorjesus.jpeg");
    raptorSprite->AddSprite("Sprites/rechauffeur.png");
    raptorTransformable->setScale({0.25f, 0.25f});
    raptorTransformable->setOrigin({raptorSprite->sprites[0].getTextureRect().width/2, raptorSprite->sprites[0].getTextureRect().height/2});

    raptorSprite->SetThisSpriteLocalPosition(1, {-90, -50});

    raptorSprite->update();

    while (window->isOpen()) {
        while (window->pollEvent(event))
            if (event.type == sf::Event::Closed) {
                window->close();
            }
            else if (event.type == 9) {
                raptorTransformable->rotate(30);
                raptorSprite->update();
            }

        window->clear(sf::Color(125,0,125,0));
        raptorSprite->render(window);
        window->display();
    }
    return 0;
}