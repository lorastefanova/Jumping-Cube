/*!
\file main.cpp
\brief Contains the entry point for the application
*/

/*! 
\mainpage IMAT2906 - 2D Platformer.
*
* This is an implementation of a 2D Platofrmer game of my own design using Box2D and SFML.
*
* The game's mechanics include:
*
* Static graphical background.
*
* Static platforms.
*
* Collectable items (coins) which disappear on player contact.
*
* A player which undergoes realistic motion and collides with other game objects.
*
* NPC with movement patterns.
*
* Moving platforms.
*
* Implementation of defined rules for winning or losing.
*
* A head-up-display (HUD).
*/

#include <Box2D/Box2D.h>
#include <SFML/Graphics.hpp>

#include "Game.h"

void main() /** Entry point for the application */
{
	sf::RenderWindow window(sf::VideoMode(1024, 800), "CW Starter"); // Open main window

	Game game; // Game class game object

	float fFrameTime = 1.f / 60.f; // Setting frames per second 

	sf::Clock clock; // Start a clock to provide time for the physics

	// Run a game loop
	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			// Window closed button pressed
			if (event.type == sf::Event::Closed)
				window.close();

			// Events on key press
			if (event.type == sf::Event::KeyPressed)
			{
				game.onKeyPress(event.key.code);
			}
		}

		float m_fElapsedTime = clock.getElapsedTime().asSeconds(); // Find out how much time has elapsed

		// If a frame has past the update the physics
		if (m_fElapsedTime > fFrameTime)
		{
			game.update(m_fElapsedTime);
			clock.restart();
		}

		window.clear(sf::Color(0,0,0));

		window.draw(game); // Draw the game
		window.display(); // Display everyhting drawn
	}

}