#pragma once

/*!
\file physicalThing.h
*/

#include <Box2D/Box2D.h>

#define DEG2RAD 0.017453f
#define RAD2DEG 57.29577f

/*! 
\class PhysicalThing
\brief A simple class with common attributes and a few const values used when creating a body
*/

class PhysicalThing {
protected:
	b2Body * m_body = nullptr; //!< Box2D body
	float mk_fDensity = 1.0f; //!< Density of the material - used to give mass
	float mk_fFriction = 0.4f; //!< Friction from movement
	float mk_fRestitution = 0.0f; //!< Restitution - bouncyness

public:
	void setUserData(void* data) { m_body->SetUserData(data); }; //!< Set the user data of the body
	b2Body * getBody() { return m_body; } //!< Get the body
};
