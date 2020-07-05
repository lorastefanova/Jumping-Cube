#pragma once

/*!
\file FinishDoor.h
*/

#include <Box2D/Box2D.h>
#include <SFML/Graphics.hpp>

#include "physicalThing.h"

/*! 
\class FinishDoor
\brief The player must reach this finish door to win the game
*/

class FinishDoor : public PhysicalThing, public sf::CircleShape
{
public:
	FinishDoor() {}; //!< Default constructor
	FinishDoor(b2World * world, sf::Vector2f position, float radius, sf::Texture* tex); //!< Complete constructor
	void onAction(b2Body * other); //!< Function for the finish door action
};

