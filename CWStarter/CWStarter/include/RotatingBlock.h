#pragma once

/*!
\file RotatingBlock.h
*/

#include <SFML/Graphics.hpp>
#include <Box2D/Box2D.h>

#include "physicalThing.h"

/*!
\class RotatingBlock
\brief A class for platforms which are rotating by a revolute joint
*/

class RotatingBlock : public sf::Drawable , public PhysicalThing
{
private:
	sf::RectangleShape m_rectangle; //!< A rectangle
	b2Body * m_anchor; //!< Body anchor
	b2RevoluteJoint * m_hinge; //!< Revolute joint
public:
	RotatingBlock() {}; //!< Default constructor
	RotatingBlock(b2World * world, sf::Vector2f position, sf::Vector2f size, sf::Vector2f anchor, float orientation, sf::Color color); // Complete constructor
	RotatingBlock(b2World * world, sf::Vector2f position, sf::Vector2f size, sf::Vector2f anchor, float orientation); // Complete constructor

	void draw(sf::RenderTarget& render, sf::RenderStates states) const; //!< Function to draw rotating block
	void update(); //!< Function to update rendering infomation 
};

