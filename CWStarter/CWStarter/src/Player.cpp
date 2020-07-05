/*!
\file Player.cpp
\brief A file to create the player body and move it
*/

#include "Player.h"

//! Player constructor
/*!
\param world a b2World - the world
\param position a sf::Vector2f - the position of the player
\param size a sf::Vector2f - the size of the player
\param tex an sf::Texture pointer - the texture used for the player
\create the player body
\the player is a dynamic body
\creating a second fixture for the foot sensor 
*/
Player::Player(b2World * world, const sf::Vector2f& position, const sf::Vector2f &size, sf::Texture* tex)
{
	b2BodyDef l_bodyDef;
	b2PolygonShape l_shape;
	b2FixtureDef l_fixtureDef;

	l_bodyDef.position.Set(position.x, position.y);
	l_bodyDef.type = b2_dynamicBody;

	m_body = world->CreateBody(&l_bodyDef);
	m_body->SetUserData(this);

	l_shape.SetAsBox(size.x * 0.5f, size.y * 0.5f);
	l_shape.m_radius = 0.0f;

	l_fixtureDef.density = mk_fDensity;
	l_fixtureDef.friction = mk_fFriction;
	l_fixtureDef.restitution = mk_fRestitution;
	l_fixtureDef.shape = &l_shape;

	m_body->CreateFixture(&l_fixtureDef);

	l_shape.SetAsBox(size.x * 0.5f, size.y * 0.5f);
	l_fixtureDef.isSensor = true;
	b2Fixture* footSensorFixture = m_body->CreateFixture(&l_fixtureDef);
	footSensorFixture->SetUserData((void*)3);

	setPosition(position);
	setSize(size);
	setOrigin(size * 0.5f);
	setTexture(tex);
}

//! Function to move the player right
/*!
\get the body's linear velocity 
\set the body's linear velocity on the x axis to 2
*/
void Player::MoveRight()
{
	b2Vec2 vel = m_body->GetLinearVelocity();
	vel.x = 2.f;
	m_body->SetLinearVelocity(vel);
}

//! Function to move the player left
/*!
\get the body's linear velocity
\set the body's linear velocity on the x axis to -2
*/
void Player::MoveLeft()
{
	b2Vec2 vel = m_body->GetLinearVelocity();
	vel.x = -2.f;
	m_body->SetLinearVelocity(vel);
}

//! Function to jump
/*!
\apply linear impulse on the y axis
*/
void Player::Jump()
{
	m_body->ApplyLinearImpulseToCenter(b2Vec2(0.0f, -1.f), true);
	
}

//! Function for the player action
/*!
\change player's color to transparent
*/
void Player::onAction(b2Body* other)
{

	setFillColor(sf::Color(255, 255, 255, 0));
}

//! Function to update
/*!
\get the body's current position
\set the body's current position 
*/
void Player::update()
{
	b2Vec2 pos = m_body->GetPosition();
	setPosition(pos.x, pos.y);
}

