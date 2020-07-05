/*!
\file FinishDoor.cpp
\brief A file to create the finish door body
*/

#include "FinishDoor.h"

//! FinishDoor constructor
/*!
\param world a b2World - the world
\param position a sf::Vector2f - the position of the door
\param radius a float - the radius of the door
\param tex an sf::Texture pointer - the texture used for the door
\create the door body
\the door is a static sensor
*/
FinishDoor::FinishDoor(b2World * world, sf::Vector2f position, float radius, sf::Texture* tex)
{
	b2BodyDef l_bodyDef;
	b2CircleShape l_shape;
	b2FixtureDef l_fixtureDef;

	l_bodyDef.position.Set(position.x, position.y);

	m_body = world->CreateBody(&l_bodyDef);
	m_body->SetUserData(this);

	l_shape.m_radius = radius;

	l_fixtureDef.density = mk_fDensity;
	l_fixtureDef.friction = mk_fFriction;
	l_fixtureDef.restitution = mk_fRestitution;
	l_fixtureDef.shape = &l_shape;

	l_fixtureDef.isSensor = true;

	m_body->CreateFixture(&l_fixtureDef);
	b2Fixture* doorFixture = m_body->CreateFixture(&l_fixtureDef);
	doorFixture->SetUserData((void*)6);

	setPosition(position);
	setRadius(radius);
	setOrigin(radius, radius);
	setTexture(tex);
}

//! Function for the door action
/*!
\param other a b2Body pointer - points to a body
\if the player collides with the door it changes color
*/
void FinishDoor::onAction(b2Body * other)
{
	setFillColor(sf::Color::Green);
}
