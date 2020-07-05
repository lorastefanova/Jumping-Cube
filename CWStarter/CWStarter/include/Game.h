#pragma once

/*!
\file Game.h
*/

#include <Box2D/Box2D.h>
#include <SFML/Graphics.hpp>
#include <vector>
#include <iostream>

#include "SFMLDebugDraw.h"

#include "Player.h"
#include "ContactListener.h"
#include "Floor.h"
#include "RotatingBlock.h"
#include "Coin.h"
#include "FinishDoor.h"
#include "MovingPlatform.h"
#include "Enemy.h"

/*!
\class Game
\brief Holds all information about the game, allows updating and rendering
*/

class Game : public sf::Drawable {
private:
	sf::View m_camera; //!< A camera that maps from physical co-ordinates to rendering co-ordinates
	sf::Vector2f m_worldSize = sf::Vector2f(8.f, 6.f); //!< Size of the physical worlds is 8 X 6 metres

	sf::Texture m_texture; //!< Texture to be used as a background
	sf::RectangleShape m_picture; //!< Picture drawn to the scene

	b2World* m_pWorld = nullptr; //!< Pointer to the Box2D world. Using pointers as BOX2D has it's own memory management
	const int mk_iVelIterations = 7; //!< On each update there will be 7 velocity iterations in the physics engine
	const int mk_iPosIterations = 5; //!< On each update there will be 5 position iterations on each update
	const b2Vec2 mk_gravity = b2Vec2(0.f, 10.f); //!< Game gravity

	bool m_debug = false; //!< Toggle for debug drawing
	SFMLDebugDraw m_debugDraw; //!< Box2D debug drawing

	Player m_player; //!< Player
	sf::Texture m_playerTexture; //!< Player texture

	Enemy m_enemy; //!< Enemy
	sf::Texture m_enemyTexture; //!< Enemy texture

	FinishDoor m_finishDoor; //!< Finish door
	sf::Texture m_doorTexture; //!< Finish door texture

	ContactListener m_listener; //!< ContactListener

	std::vector<Floor> m_floor; //!< Vector of static platforms

	std::vector<RotatingBlock> m_rotatingBlock; //!< Vector of rotating platforms

	std::vector<Coin> m_coins; //!< Vector of coins

	std::vector<MovingPlatform> m_movingPlatform; //!< Vector of moving platforms

	int m_jumpTimeout = 0; //!< Jump timeout
	
	sf::Font m_font; //!< Font for the HUD
	sf::Text score; //!< Score text
	sf::Text scoreNum; //!< Score count
	sf::Text win; //!< You win text
	sf::Text lose; //!< You lose text
	
public:
	Game(); //!< Constructor which sets up the game
	~Game(); //!< Destructor which cleans all the pointer memory up
	
	void onKeyPress(sf::Keyboard::Key code); //!< Function to use the keyboard
	void update(float timestep); //!< Function to update the game with given timestep
	void draw(sf::RenderTarget &target, sf::RenderStates states) const; //!< Function to draw the game to the render context
	void toggleDebug(); //!< Toggle for debug drawing
};