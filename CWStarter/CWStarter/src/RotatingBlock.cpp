/*!
\file RotatingBlock.cpp
\brief A file to create the rotating platform body with a revolute joint
*/

#include "RotatingBlock.h"

//! RotatingBlock constructor
/*!
\param world a b2World - the world
\param position a sf::Vector2f - the position of the rotating block
\param size a sf::Vector2f - the size of the rotating block
\param anchor an sf::Vector2f - the anchor for  the revolute joint
\param orientation a float - the orientation of the rotating block
\param color an sf::Color - the color used for the rotating block
\create the moving platform body
\the platform is a dynamic body
\create the revolute joint
*/
RotatingBlock::RotatingBlock(b2World * world, sf::Vector2f position, sf::Vector2f size, sf::Vector2f anchor, float orientation, sf::Color color)
{
	b2BodyDef l_bodyDef;
	b2PolygonShape l_shape;
	b2FixtureDef l_fixtureDef;

	l_shape.SetAsBox(size.x * 0.5f, size.y * 0.5f);
	l_shape.m_radius = 0.0f;

	l_fixtureDef.density = mk_fDensity;
	l_fixtureDef.friction = mk_fFriction;
	l_fixtureDef.restitution = mk_fRestitution;
	l_fixtureDef.shape = &l_shape;

	l_bodyDef.position.Set(position.x, position.y);
	l_bodyDef.angle = orientation * DEG2RAD;
	l_bodyDef.type = b2_dynamicBody;

	m_body = world->CreateBody(&l_bodyDef);
	m_body->CreateFixture(&l_fixtureDef);
	m_body->SetAngularDamping(0.1f);

	l_bodyDef.type = b2_staticBody;

	b2CircleShape l_circ;
	l_circ.m_radius = fminf(size.x / 2.0f, size.y / 2.0f);
	l_fixtureDef.shape = &l_circ;

	m_anchor = world->CreateBody(&l_bodyDef);
	m_anchor->CreateFixture(&l_fixtureDef);

	b2RevoluteJointDef jointDef;
	jointDef.bodyA = m_anchor;
	jointDef.bodyB = m_body;
	jointDef.collideConnected = false;
	jointDef.localAnchorA.Set(0.f, 0.f);
	jointDef.localAnchorB.Set(anchor.x, anchor.y);
	m_hinge = (b2RevoluteJoint*)world->CreateJoint(&jointDef);

	m_rectangle.setPosition(position);
	m_rectangle.setSize(size);
	m_rectangle.setOrigin(size * 0.5f);
	m_rectangle.setRotation(orientation);
	m_rectangle.setFillColor(color);
}

//! RotatingBlock second constructor
/*!
\
*/
RotatingBlock::RotatingBlock(b2World * world, sf::Vector2f position, sf::Vector2f size, sf::Vector2f anchor, float orientation)
{

}

//! Function to update
/*!
\get the body's current position
\set the body's current position 
\get the body's current angle
\set the body's current angle
*/
void RotatingBlock::update()
{
	b2Vec2 pos = m_body->GetPosition();
	m_rectangle.setPosition(pos.x, pos.y);
	float angle = m_body->GetAngle()* RAD2DEG;
	m_rectangle.setRotation(angle);
}

//! Function to draw
/*!
\draw the block to the target window
*/
void RotatingBlock::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	target.draw(m_rectangle);
}
