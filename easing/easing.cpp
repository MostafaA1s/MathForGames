#include <SFML/Graphics.hpp>
#include "Quint.h"


int main()
{
	sf::RenderWindow window(sf::VideoMode(800, 600), "SFML works!");
	window.setFramerateLimit(60);
	sf::CircleShape shape(20.0f);
	shape.setPosition(400, 300);
	shape.setOrigin(20, 20);
	shape.setFillColor(sf::Color::Green);


	sf::Vector2i mousePos;
	sf::Vector2f initPosition(shape.getPosition());

	sf::Clock clock;

	float timer;

	float timeToMove = -1.f;

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
			if (event.type == sf::Event::MouseButtonReleased)
			{
				mousePos = sf::Mouse::getPosition(window);
				timeToMove = 1.f;
				initPosition = shape.getPosition();
				clock.restart();
			}
		}

		timer = clock.getElapsedTime().asSeconds();

		if (timer < timeToMove)
		{
			shape.setPosition(Quint::easeInOut(timer, initPosition.x, mousePos.x - initPosition.x, timeToMove),
				Quint::easeInOut(timer, initPosition.y, mousePos.y - initPosition.y, timeToMove));

		}


		window.clear();
		window.draw(shape);
		window.display();
	}

	return 0;
}