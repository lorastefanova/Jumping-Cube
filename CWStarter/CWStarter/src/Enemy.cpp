/*!
\file Enemy.cpp
\brief A file to create the enemy body and move it
*/

#include "Enemy.h"

//! Enemy constructor
/*!
\param world a b2World - the world
\param position a sf::Vector2f - the position of the enemy
\param radius a float - the radius of the enemy
\param orientation a float - the orientation of the enemy
\param tex an sf::Texture pointer - the texture used for the enemy
\create the enemy body
\the enemy is a dynamic body
*/
Enemy::Enemy(b2World * world, sf::Vector2f position, float radius, float orientation, sf::Texture* tex)
{
	b2BodyDef l_bodyDef;
	b2CircleShape l_shape;
	b2FixtureDef l_fixtureDef;

	l_bodyDef.type = b2_dynamicBody;
	l_bodyDef.position.Set(position.x, position.y);
	l_bodyDef.angle = orientation * DEG2RAD;

	m_body = world->CreateBody(&l_bodyDef);
	m_body->SetUserData(this);

	l_shape.m_radius = radius;

	l_fixtureDef.density = mk_fDensity;
	l_fixtureDef.friction = mk_fFriction;
	l_fixtureDef.restitution = mk_fRestitution;
	l_fixtureDef.shape = &l_shape;

	m_body->CreateFixture(&l_fixtureDef);
	b2Fixture* enemyFixture = m_body->CreateFixture(&l_fixtureDef);
	enemyFixture->SetUserData((void*)5);

	setPosition(position);
	setRadius(radius);
	setOrigin(radius, radius);
	setRotation(orientation);
	setTexture(tex);
}

//! Function to move the enemy
/*!
\gets the current position of the body 
\if it's less than 10.6 on the x axis - goes right
\if it's more than 13.5 on the x axis - goes left
*/
void Enemy::Move()
{
	if (m_body->GetPosition().x < 10.6f)
	{
		b2Vec2 vel = m_body->GetLinearVelocity();
		vel.x = 2.5f;
		m_body->SetLinearVelocity(vel);
	}
	else if (m_body->GetPosition().x > 13.5f)
	{
		b2Vec2 vel = m_body->GetLinearVelocity();
		vel.x = -2.5f;
		m_body->SetLinearVelocity(vel);
	}
}

//! Function to update
/*!
\gets the current position of the body
\sets the current position of the body
\gets the current angle of the body
\sets the current angle of the body
*/
void Enemy::update()
{

	b2Vec2 pos = m_body->GetPosition();
	setPosition(pos.x, pos.y);
	float angle = m_body->GetAngle()* RAD2DEG;
	setRotation(angle);
}