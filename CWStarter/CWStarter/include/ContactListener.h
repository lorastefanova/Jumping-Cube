#pragma once

/*!
\file ContactListener.h
*/

#include <Box2D\Box2D.h>

#include "Coin.h"
#include "Player.h"
#include "FinishDoor.h"

/*! 
\class ContactListener
\brief A listener which listens for contacts between game objects and sensors
*/

class ContactListener : public b2ContactListener
{
public:
	void BeginContact(b2Contact* contact); //!< Function called when two fixtures begin to touch
	void EndContact(b2Contact* contact); //!< Function called when two fixtures cease to touch

	int numFootContacts = 0; //!< Number of player foot contacts
};