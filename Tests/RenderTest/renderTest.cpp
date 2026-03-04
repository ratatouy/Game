#include <iostream>

#include <SFML/Graphics.hpp>
#include "Engine/RenderEngine.hpp"

int main() {
	RenderEngine renderEngine = RenderEngine();

	std::cout << sf::Shader::Fragment << std::endl;

	renderEngine.addShaderObject("assets/Shaders/FragmentShaders/fire.glsl", sf::Shader::Fragment);

	while (renderEngine.getWindow()->isOpen()) {
		// Event handling
		sf::Event event;

		while (renderEngine.getWindow()->pollEvent(event)) {
			// Exit the app when a key is pressed
			if (event.type == sf::Event::Closed) 
				renderEngine.getWindow()->close();
		}


		// Draw the sprite with the shader on it
		renderEngine.getWindow()->clear();
		renderEngine.update(1.0f/60.0f);
		renderEngine.render();
		renderEngine.getWindow()->display();
	}

	return 0;
}
