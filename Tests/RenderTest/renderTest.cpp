#include <iostream>

#include <SFML/Graphics.hpp>
#include "Engine/RenderEngine.hpp"

int main() {
	RenderEngine renderEngine = RenderEngine();

	std::cout << sf::Shader::Fragment << std::endl;

	// renderEngine.addShaderObject("assets/Shaders/FragmentShaders/fire.glsl", sf::Shader::Fragment);
	int width = renderEngine.getWindow()->getSize().x;
    int height = renderEngine.getWindow()->getSize().y;

	std::cout << width << height << std::endl;

	renderEngine.my_shape.setSize(sf::Vector2f(width, height));
	renderEngine.my_shader.loadFromFile("assets/Shaders/FragmentShaders/fire.glsl", sf::Shader::Fragment);

	renderEngine.my_shader.setUniform("resolution", sf::Glsl::Vec2(width, height));

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
		renderEngine.tick();
		renderEngine.update();
		renderEngine.render();
		renderEngine.getWindow()->display();
	}

	return 0;
}
