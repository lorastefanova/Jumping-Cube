#pragma once

/*!
\file Enemy.h
*/

#include <Box2D/Box2D.h>
#include <SFML/Graphics.hpp>

#include "physicalThing.h"

/*! 
\class Enemy
\brief NPC with movement patterns
*/

class Enemy : public sf::CircleShape, public PhysicalThing
{
private:
	bool m_enemyLeft; //!< Is the enemy going left?

public:
	Enemy() {}; //!< Default Constructor
	Enemy(b2World * world, sf::Vector2f position, float radius, float orientation, sf::Texture* tex); //!< Complete contructor

	void Move(); //!< Function to move the enemy
	void update(); //!< Function to update rendering infomation 
};
