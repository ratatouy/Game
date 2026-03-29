#include <iostream>

#include <SFML/Graphics.hpp>
#include "Engine/RenderEngine.hpp"

int main() {
	RenderEngine* renderEngine = new RenderEngine(nullptr);

	int width = renderEngine->getWindow()->getSize().x;
    int height = renderEngine->getWindow()->getSize().y;

	sf::RectangleShape* shape = new sf::RectangleShape({(float)width/2, (float)height});
	shape->setPosition(width/2, 0);

	sf::RectangleShape* shape2 = new sf::RectangleShape({(float)width/2, (float)height});


	// Create a Drawable object then attach a shader
	renderEngine->addDrawable("chauffeur", shape2);
	renderEngine->attachShaderToDrawable("chauffeur", "assets/Shaders/FragmentShaders/fire.glsl", sf::Shader::Fragment);

	// Create a ShaderDrawable Directly
	renderEngine->addShaderDrawable("fire", shape, "assets/Shaders/FragmentShaders/fire.glsl", sf::Shader::Fragment);

	/// THIS WILL RESULT IN 2 SHADERS EVEN IF ONLY ONE APPEARS
	/// The reason is just that both are following the mouse here

	// Render Loop
	while (renderEngine->getWindow()->isOpen()) {
		// Event handling
		sf::Event event;

		while (renderEngine->getWindow()->pollEvent(event)) {
			// Exit the app when a key is pressed
			if (event.type == sf::Event::Closed) 
				renderEngine->getWindow()->close();
		}

		// Draw the sprites with the shader on it
		renderEngine->getWindow()->clear(sf::Color(155, 255, 0, 0));
		renderEngine->update();
		renderEngine->render();
		renderEngine->getWindow()->display();
	}

	delete shape;
	delete shape2;
	delete renderEngine;

	return 0;
}
