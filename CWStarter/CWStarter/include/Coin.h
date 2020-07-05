#pragma once

/*!
\file Coin.h
*/

#include <Box2D/Box2D.h>
#include <SFML/Graphics.hpp>

#include "physicalThing.h"

/*! 
\class Coin
\brief A static sensor. Collectible which disappears on player contact
*/

class Coin : public sf::CircleShape, public PhysicalThing
{
public:
	Coin() {}; //!< Default constructor
	Coin(b2World * world, sf::Vector2f position, float radius ); //!< Complete constructor

	bool isCollected = false; //!< Is the coin collected?
};

