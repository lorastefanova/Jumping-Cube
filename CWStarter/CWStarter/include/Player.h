#pragma once

/*!
\file Player.h
*/

#include <Box2D/Box2D.h>
#include <SFML/Graphics.hpp>

#include "physicalThing.h"

/*!
\class Player
\brief A class for the player which undergoes realistic motion and collides with other game objects
*/

class Player : public sf::RectangleShape , public PhysicalThing
{
private:
public:
	Player() {}; //!< Default Constructor
	Player(b2World * world, const sf::Vector2f& position, const sf::Vector2f &size, sf::Texture* tex); //!< Complete contructor

	void update(); //!< Function to update rendering infomation 
	void MoveRight(); //!< Function to move right
	void MoveLeft(); //!< Function to move left
	void Jump(); //!< Function to jump
	void onAction(b2Body* other); //!< Function for player on actio

	int score = 0; //!< Score
	bool won = false; //!< Did the player win?
	bool lost = false; //!< Did the player lose?
};
