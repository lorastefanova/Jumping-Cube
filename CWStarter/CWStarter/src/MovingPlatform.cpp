/*!
\file MovingPlatform.cpp
\brief A file to create the moving platform body moved by a motor joint
*/

#include "MovingPlatform.h"

//! MovingPlatform constructor
/*!
\param world a b2World - the world
\param position a sf::Vector2f - the position of the moving platform
\param size a sf::Vector2f - the size of the moving platform
\param orientation a float - the orientation of the moving platform
\param color an sf::Color - the color used for the moving platform
\param anchor a b2Body pointer - the body anchor
\create the moving platform body 
\the platform is a dynamic body
\create the motor joint
*/
MovingPlatform::MovingPlatform(b2World * world, sf::Vector2f position, sf::Vector2f size, float orientation, sf::Color color, b2Body * anchor)
{
	b2BodyDef l_bodyDef;
	b2PolygonShape l_shape;
	b2FixtureDef l_fixtureDef;
	b2MotorJointDef mjd;

	l_bodyDef.position.Set(position.x, position.y);
	l_bodyDef.angle = orientation * DEG2RAD;
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

	mjd.bodyA = anchor;
	mjd.bodyB = m_body;
	mjd.linearOffset = b2Vec2(m_body->GetPosition().x - anchor->GetPosition().x, 0.f);
	mjd.angularOffset = 0.0f;
	mjd.maxForce = 1000.f;
	mjd.maxTorque = 1000.f;

	m_motorJoint = (b2MotorJoint*)world->CreateJoint(&mjd);

	setPosition(position);
	setSize(size);
	setOrigin(size * 0.5f);
	setRotation(orientation);
	setFillColor(color);

}

//! Function to move the platform
/*!
\if the platform is moving up - move it down
\if the platform is moving down - move it up
*/
void MovingPlatform::Move(float timestep)
{
	elapsedTime += timestep;
	float t = elapsedTime / motionTime;

	float vel = 1.5f;
	float offsetX = m_motorJoint->GetLinearOffset().x;
	float offsetY;

	if (m_platformUp)
	{
		float t = -vel * timestep;
		offsetY = m_motorJoint->GetLinearOffset().y + t;
		if (offsetY < -0.2f)
		{
			offsetY = -0.2f;
			m_platformUp = !m_platformUp;
		}
	}
	else
	{
		float t = vel * timestep;
		offsetY = m_motorJoint->GetLinearOffset().y + t;
		if (offsetY > 3.3f)
		{
			offsetY = 3.3f;
			m_platformUp = !m_platformUp;
		}
	}
	m_motorJoint->SetLinearOffset(b2Vec2(offsetX, offsetY));
}

//! Function to update
/*!
\gets the current position of the body
\sets the current position of the body
\gets the current angle of the body
\sets the current angle of the body
*/
void MovingPlatform::update()
{
	b2Vec2 pos = m_body->GetPosition();
	setPosition(pos.x, pos.y);
	float angle = m_body->GetAngle()* RAD2DEG;
	setRotation(angle);
}
