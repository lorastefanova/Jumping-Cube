#pragma once

/*!
\file MovingPlatform.h
*/

#include <Box2D/Box2D.h>
#include <SFML/Graphics.hpp>

#include "physicalThing.h"

/*! 
\class MovingPlatform
\brief A class for platforms which are moved up and down by a motor joint
*/

class MovingPlatform : public sf::RectangleShape, public PhysicalThing
{
private:
	b2MotorJoint * m_motorJoint; //!< Motor joint

	bool m_platformUp; //!< Is the platform going up?
	float elapsedTime; //!< Elapsed time
	float motionTime = 1.5; //!< Motion time

public:
	MovingPlatform() {}; //!< Default Constructor
	MovingPlatform(b2World * world, sf::Vector2f position, sf::Vector2f size, const float orientation, sf::Color color, b2Body * anchor); //!< Complete contructor
	
	void update(); //!< Function to update rendering infomation 
	void Move(float timestep); //!< Function to move the platform
};