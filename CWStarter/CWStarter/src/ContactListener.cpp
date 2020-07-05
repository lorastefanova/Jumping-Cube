/*!
\file ContactListener.cpp
\brief A contact listener file to listen for collision
*/

#include "ContactListener.h"

//! Function when contact between fixtures begins
/*!
\uses body user data to distingwish bodies.
\
\for player ground collision:
\checks if fixture A or B is the foor sensor
\adds to number of foot contacts
\
\for coin collision:
\checks if fixture A or B is the coin
\checks if fixture A or B is the player
\coin is collected
\adds one to the score
\
\for enemy collision:
\checks if fixture A or B is the enemy
\checks if fixture A or B is the player
\apply onAction function from the player class
\player lost
\
\for finish door collision:
\checks if fixture A or B is the door
\checks if fixture A or B is the player
\apply onAction function from the player class
\apply onAction function from the finishDoor class
\player won
*/
void ContactListener::BeginContact(b2Contact * contact)
{
	b2Body* bodyA = contact->GetFixtureA()->GetBody();
	b2Body* bodyB = contact->GetFixtureB()->GetBody();



	/* Player ground collision */
	void* playerUserData = contact->GetFixtureA()->GetUserData();
	if ((int)playerUserData == 3)
		numFootContacts++;

	playerUserData = contact->GetFixtureB()->GetUserData();
	if ((int)playerUserData == 3)
		numFootContacts++;



	/* Coin collision */
	void* coinUserData = contact->GetFixtureA()->GetUserData();
	playerUserData = contact->GetFixtureB()->GetUserData();
	if ((int)coinUserData == 4 && (int)playerUserData == 3)
	{
		Coin * coin = static_cast<Coin *>(bodyA->GetUserData());
		coin->isCollected = true;

		Player * player = static_cast<Player *>(bodyA->GetUserData());
		player->score++;
	}

	coinUserData = contact->GetFixtureB()->GetUserData();
	playerUserData = contact->GetFixtureA()->GetUserData();
	if ((int)coinUserData == 4 && (int)playerUserData == 3)
	{
		Coin * coin = static_cast<Coin *>(bodyB->GetUserData());
		coin->isCollected = true;

		Player * player = static_cast<Player *>(bodyA->GetUserData());
		player->score++;
	}

	

	/* Enemy collision */
	void* enemyUserData = contact->GetFixtureA()->GetUserData();
	playerUserData = contact->GetFixtureB()->GetUserData();
	if ((int)enemyUserData == 5 && (int)playerUserData == 3)
	{
		Player * player = static_cast<Player *>(bodyA->GetUserData());
		player->onAction(bodyB);

		player = static_cast<Player *>(bodyA->GetUserData());
		player->lost=true;
	}

	enemyUserData = contact->GetFixtureB()->GetUserData();
	playerUserData = contact->GetFixtureA()->GetUserData();
	if ((int)enemyUserData == 5 && (int)playerUserData == 3)
	{
		Player * player = static_cast<Player *>(bodyA->GetUserData());
		player->onAction(bodyA);

		player = static_cast<Player *>(bodyA->GetUserData());
		player->lost = true;
	}



	/* Finish portal collision */
	void* doorUserData = contact->GetFixtureA()->GetUserData();
	playerUserData = contact->GetFixtureB()->GetUserData();
	if ((int)doorUserData == 6 && (int)playerUserData == 3)
	{
		FinishDoor * door = static_cast<FinishDoor *>(bodyA->GetUserData());
		door->onAction(bodyB);

		Player * player = static_cast<Player *>(bodyA->GetUserData());
		player->onAction(bodyB);

		player = static_cast<Player *>(bodyA->GetUserData());
		player->won = true;
	}

	doorUserData = contact->GetFixtureB()->GetUserData();
	playerUserData = contact->GetFixtureA()->GetUserData();
	if ((int)doorUserData == 6 && (int)playerUserData == 3)
	{
		FinishDoor * door = static_cast<FinishDoor *>(bodyB->GetUserData());
		door->onAction(bodyA);

		Player * player = static_cast<Player *>(bodyA->GetUserData());
		player->onAction(bodyA);

		player = static_cast<Player *>(bodyA->GetUserData());
		player->won = true;
	}
}

//! Function when contact between fixtures ends
/*!
\uses body user data to distingwish bodies.
\
\for player ground collision:
\checks if fixture A or B is the foor sensor
\takes away from number of foot contacts
*/
void ContactListener::EndContact(b2Contact * contact)
{
	/* Player ground collision */
	void* playerUserData = contact->GetFixtureA()->GetUserData();
	if ((int)playerUserData == 3)
		numFootContacts--;
	
	playerUserData = contact->GetFixtureB()->GetUserData();
	if ((int)playerUserData == 3)
		numFootContacts--;
}