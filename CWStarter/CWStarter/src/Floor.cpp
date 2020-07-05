/*!
\file Floor.cpp
\brief A file to create the static platform body
*/

#include "Floor.h"

//! Floor constructor
/*!
\param world a b2World - the world
\param position a sf::Vector2f - the position of the platform
\param size a sf::Vector2f - the size of the platform
\param color an sf::Color - the color used for the platform
\create the platform body
*/
Floor::Floor(b2World * world, sf::Vector2f position, sf::Vector2f size, sf::Color color)
{
	b2BodyDef l_bodyDef;
	b2PolygonShape l_shape;
	b2FixtureDef l_fixtureDef;

	l_bodyDef.position.Set(position.x, position.y);

	m_body = world->CreateBody(&l_bodyDef);
	m_body->SetUserData(this);

	l_shape.SetAsBox(size.x * 0.5f, size.y * 0.5f);
	l_shape.m_radius = 0.0f;

	l_fixtureDef.density = mk_fDensity;
	l_fixtureDef.friction = mk_fFriction;
	l_fixtureDef.restitution = mk_fRestitution;
	l_fixtureDef.shape = &l_shape;

	m_body->CreateFixture(&l_fixtureDef);

	setPosition(position);
	setSize(size);
	setOrigin(size * 0.5f);
	setOutlineThickness(0.f);
	setFillColor(color);
}