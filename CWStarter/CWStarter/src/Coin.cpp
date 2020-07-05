/*!
\file Coin.cpp
\brief A file to create the coin body
*/

#include "Coin.h"

//! Coin constructor
/*!
\param world a b2World - the world.
\param position a sf::Vector2f - the position of the coin.
\param radius a float - the radius of the coin.
\create the coin body
\the coin is a static sensor
*/
Coin::Coin(b2World * world, sf::Vector2f position, float radius)
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
	b2Fixture* coinFixture = m_body->CreateFixture(&l_fixtureDef);
	coinFixture->SetUserData((void*)4);

	setPosition(position);
	setRadius(radius);
	setOrigin(radius, radius);
	setFillColor(sf::Color::Yellow);
}

