#pragma once

/*!
\file Floor.h
*/

#include <Box2D/Box2D.h>
#include <SFML/Graphics.hpp>

#include "physicalThing.h"

/*! 
\class Floor
\brief A class to create all static platforms
*/

class Floor : public sf::RectangleShape, public PhysicalThing
{
private:
public:
	Floor() {}; //!< Default Constructor
	Floor(b2World * world, sf::Vector2f position, sf::Vector2f size, sf::Color color); //!< Complete contructor
};

