/*!
\file Game.cpp
\brief A file to hold all information about the game, allows updating and rendering
*/

#include "Game.h"

//! Game constructor
/*!
\loading the font
\initialising the background
\setting the camea view
\creating the world
\initializing the player
\initialising the enemy
\initializing a vector of static platforms
\initializing a vector of rotating blocks
\initializing a vector of moving platforms
\initializing a vector of coins
\initializing the finish door
\creating player score text (HUD)
\creating You win! message (HUD)
\creating You los! message (HUD)
*/
Game::Game()
{
	// Font
	m_font.loadFromFile("./assets/fonts/Font.ttf");
	
	// Background
	m_texture.loadFromFile("./assets/images/background.jpg");
	m_picture.setSize(sf::Vector2f(32.f, 24.f));
	m_picture.setPosition(-3.5f, -12.f);
	m_picture.setTexture(&m_texture);

	// Camera
	m_camera.setSize(m_worldSize);
	
	// World
	m_pWorld = new b2World(mk_gravity);

	// Debug draw
	m_debugDraw.setWorld(m_pWorld);

	// Player
	m_playerTexture.loadFromFile("./assets/images/smile.jpg");
	m_player = Player(m_pWorld, sf::Vector2f(0.5f, 5.f), sf::Vector2f(0.3f, 0.3f), &m_playerTexture);
	m_player.setUserData(&m_player);

	// Enemy
	m_enemyTexture.loadFromFile("./assets/images/enemy.png");
	m_enemy = Enemy(m_pWorld, sf::Vector2f(10.5f, 5.f), 0.15f, 0.0f, &m_enemyTexture);
	m_enemy.setUserData(&m_enemy);

	// Static platforms
	m_floor.resize(11);
	m_floor[0] = Floor(m_pWorld, sf::Vector2f(-1.f, 6.5f), sf::Vector2f(5.f, 1.5f), sf::Color::Black);
	m_floor[1] = Floor(m_pWorld, sf::Vector2f(12.f, 6.5f), sf::Vector2f(4.f, 1.5f), sf::Color::Black);
	m_floor[2] = Floor(m_pWorld, sf::Vector2f(4.f, 2.3f), sf::Vector2f(1.f, 0.17f), sf::Color::Black);
	m_floor[3] = Floor(m_pWorld, sf::Vector2f(7.4f, 5.f), sf::Vector2f(2.f, 0.17f), sf::Color::Black);
	m_floor[4] = Floor(m_pWorld, sf::Vector2f(17.9f, 6.2f), sf::Vector2f(1.f, 2.f), sf::Color::Black);
	m_floor[5] = Floor(m_pWorld, sf::Vector2f(17.f, 2.9f), sf::Vector2f(1.f, 0.17f), sf::Color::Black);
	m_floor[6] = Floor(m_pWorld, sf::Vector2f(18.8f, 2.9f), sf::Vector2f(1.f, 0.17f), sf::Color::Black);
	m_floor[7] = Floor(m_pWorld, sf::Vector2f(20.5f, 2.5f), sf::Vector2f(0.5f, 0.17f), sf::Color::Black);
	m_floor[8] = Floor(m_pWorld, sf::Vector2f(24.5f, 4.5f), sf::Vector2f(2.f, 5.f), sf::Color::Black);
	m_floor[9] = Floor(m_pWorld, sf::Vector2f(20.2f, 6.2f), sf::Vector2f(1.f, 2.f), sf::Color::Black);
	m_floor[10] = Floor(m_pWorld, sf::Vector2f(11.5f, 7.f), sf::Vector2f(30.f, 0.17f), sf::Color::Black);

	for (Floor& floor : m_floor) floor.setUserData(&floor);

	// Rotating block
	m_rotatingBlock.resize(4);
	m_rotatingBlock[0] = RotatingBlock(m_pWorld, sf::Vector2f(6.f, 2.6f), sf::Vector2f(1.f, 0.15f), sf::Vector2f(0.f, 0.f), 0.f, sf::Color (255, 153, 255));
	m_rotatingBlock[1] = RotatingBlock(m_pWorld, sf::Vector2f(7.5f, 2.6f), sf::Vector2f(1.f, 0.15f), sf::Vector2f(0.f, 0.f), 0.f, sf::Color(255, 153, 255));
	m_rotatingBlock[2] = RotatingBlock(m_pWorld, sf::Vector2f(9.f, 2.6f), sf::Vector2f(1.f, 0.15f), sf::Vector2f(0.f, 0.f), 0.f, sf::Color(255, 153, 255));
	m_rotatingBlock[3] = RotatingBlock(m_pWorld, sf::Vector2f(10.5f, 2.6f), sf::Vector2f(1.f, 0.15f), sf::Vector2f(0.f, 0.f), 0.f, sf::Color(255, 153, 255));

	for (RotatingBlock& block : m_rotatingBlock) block.setUserData(&block);

	// Moving platforms
	m_movingPlatform.resize(3);
	m_movingPlatform[0] = MovingPlatform(m_pWorld, sf::Vector2f(15.2f, 3.f), sf::Vector2f(1.f, 0.17f), 0.0f, sf::Color(153, 153, 255), m_floor[7].getBody());
	m_movingPlatform[1] = MovingPlatform(m_pWorld, sf::Vector2f(22.f, 3.f), sf::Vector2f(1.f, 0.17f), 0.0f, sf::Color(153, 153, 255), m_floor[7].getBody());
	m_movingPlatform[2] = MovingPlatform(m_pWorld, sf::Vector2f(2.5f, 3.f), sf::Vector2f(0.7f, 0.17f), 0.0f, sf::Color(153, 153, 255), m_floor[7].getBody());

	for (MovingPlatform& platform : m_movingPlatform) platform.setUserData(&platform);

	// Coins
	m_coins.resize(13);
	m_coins[0] = Coin(m_pWorld, sf::Vector2f(2.5f, 3.f), 0.08f);
	m_coins[1] = Coin(m_pWorld, sf::Vector2f(4.f, 2.1f), 0.08f);
	m_coins[2] = Coin(m_pWorld, sf::Vector2f(6.f, 2.4f), 0.08f);
	m_coins[3] = Coin(m_pWorld, sf::Vector2f(7.5f, 2.4f), 0.08f);
	m_coins[4] = Coin(m_pWorld, sf::Vector2f(9.f, 2.4f), 0.08f);
	m_coins[5] = Coin(m_pWorld, sf::Vector2f(10.5f, 2.4f), 0.08f);
	m_coins[6] = Coin(m_pWorld, sf::Vector2f(17.f, 2.7f), 0.08f);
	m_coins[7] = Coin(m_pWorld, sf::Vector2f(18.8f, 2.7f), 0.08f);
	m_coins[8] = Coin(m_pWorld, sf::Vector2f(20.5f, 2.3f), 0.08f);
	m_coins[9] = Coin(m_pWorld, sf::Vector2f(17.9f, 5.1f), 0.08f);
	m_coins[10] = Coin(m_pWorld, sf::Vector2f(20.2f, 5.1f), 0.08f);
	m_coins[11] = Coin(m_pWorld, sf::Vector2f(11.2f, 5.6f), 0.08f);
	m_coins[12] = Coin(m_pWorld, sf::Vector2f(13.f, 5.6f), 0.08f);

	for (Coin& coins : m_coins) coins.setUserData(&coins);

	// Finish door
	m_doorTexture.loadFromFile("./assets/images/finish.png");
	m_finishDoor = FinishDoor(m_pWorld, sf::Vector2f (24.5f, 1.5f), 0.85f, &m_doorTexture);
	m_finishDoor.setUserData(&m_finishDoor);

	m_pWorld->SetContactListener(&m_listener);

	// Score
	score.setFont(m_font);
	score.setString ("Score: ");
	score.setCharacterSize(30);
	score.scale(0.01, 0.01);
	score.setFillColor(sf::Color::Black);
	score.setStyle(sf::Text::Bold);

	scoreNum.setFont(m_font);
	scoreNum.setCharacterSize(30);
	scoreNum.scale(0.01, 0.01);
	scoreNum.setStyle(sf::Text::Bold);
	scoreNum.setFillColor(sf::Color::Black);

	// Win message
	win.setFont(m_font);
	win.setString("You won!");
	win.setCharacterSize(150);
	win.scale(0.01, 0.01);
	win.setFillColor(sf::Color::Transparent);
	win.setStyle(sf::Text::Bold);

	// Lose message
	lose.setFont(m_font);
	lose.setString("You lost!");
	lose.setCharacterSize(150);
	lose.scale(0.01, 0.01);
	lose.setFillColor(sf::Color::Transparent);
	lose.setStyle(sf::Text::Bold);
	
}

//! Game destructor
/*!
\deleting the world
*/
Game::~Game()
{
	delete m_pWorld;
	m_pWorld = nullptr;
}

//! Function to update all game objects
/*!
\updating the world
\moving the camera
\moving the enemy
\moving the platforms
\updating the player
\updating the enemy
\updating the rotating blocks
\updating the moving platforms
\preventing double jumping
\delete debug shapes
\updating coins user data
\destroying coin body on player contact
\setting score position
\updating score count
\setting You win! message position
\setting You lose! message position
\if the player won or lost display message
*/
void Game::update(float timestep)
{
	// World
	m_pWorld->Step(timestep, mk_iVelIterations, mk_iVelIterations);

	// Camera
	m_camera.setCenter(m_player.getPosition().x, 3.5f);
	
	// Moving game objects
	m_enemy.Move();

	for (MovingPlatform& platform : m_movingPlatform) platform.Move(timestep);

	// Update game objects
	m_player.update();
	m_enemy.update();

	for (RotatingBlock& block : m_rotatingBlock) block.update();
	for (MovingPlatform& platform : m_movingPlatform) platform.update();

	// Jump timeout
	m_jumpTimeout--;

	// Debug draw
	if (m_debug) m_debugDraw.clear();

	// Set coin user data
	for (Coin& coins : m_coins) coins.setUserData(&coins);

	// Destroy coin when collected
	for (std::vector<Coin>::iterator it = m_coins.begin(); it != m_coins.end(); ++it)
	{
		if (it->isCollected == true)
		{
			m_pWorld->DestroyBody(it->getBody());
			m_coins.erase(it);
			break;
		}
	}

	// Score  
	score.setPosition(m_player.getPosition().x - 3.5, .7f);
	scoreNum.setPosition(m_player.getPosition().x - 2.5, .7f);
	scoreNum.setString(std::to_string(m_player.score));

	// Win/Lose message
	win.setPosition(m_player.getPosition().x -2.7f, 3.f);
	lose.setPosition(m_player.getPosition().x -2.7f , 3.0f);

	// When to display win/lose message
	if (m_player.getPosition().y > 6.f)
		m_player.lost = true;

	if (m_player.won == true) 
	{
		win.setFillColor(sf::Color::Green);
	}

	if (m_player.lost == true)
	{
		lose.setFillColor(sf::Color::Red);
	}
}

//! Function to draw all game objects
/*!
\setting the camera view
\drawing the background
\drawing the player
\drawing the finish door
\drawing a vector of coins
\drawing the enemy
\drawing a vector of static platforms
\drawing a vector of rotating blocks
\drawing a vector of moving platforms
\drawing score HUD
\drawing You win! message
\drawing You lose! message
\debug drawing
*/
void Game::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
	target.setView(m_camera);
	target.draw(m_picture);

	target.draw(m_player);
	target.draw(m_finishDoor);

	for (auto coins : m_coins) target.draw(coins);

	target.draw(m_enemy);

	for (auto floor : m_floor) target.draw(floor);
	for (auto block : m_rotatingBlock) target.draw(block);
	for (auto platform : m_movingPlatform) target.draw(platform);

	target.draw(score);
	target.draw(scoreNum);
	target.draw(win);
	target.draw(lose);

	if (m_debug) target.draw(m_debugDraw);
}

//! Function for keyboard input
/*!
\if key Tab is pressed - toggle debug draw
\if up arrow key pressed - player jumps
\if right arow key pressed - player moves right
\if left arow key pressed - player moves left
*/
void Game::onKeyPress(sf::Keyboard::Key code)
{
	switch (code)
	{
	case sf::Keyboard::Tab:
		toggleDebug();
		break;

	case sf::Keyboard::Up:
		if (m_player.getFillColor() == sf::Color(255, 255, 255, 0)) break;
		if (m_player.getPosition().y > 6.f) break;
		if (m_listener.numFootContacts < 1) break;
		if (m_jumpTimeout > 0) break;

		m_player.Jump();
		m_jumpTimeout = 15;
		break;

	case sf::Keyboard::Right:
		if (m_player.getFillColor() == sf::Color(255, 255, 255, 0)) break;
		if (m_player.getPosition().x > 24.f) break;
		if (m_player.getPosition().y > 6.f) break;
	
		m_player.MoveRight();
		break;

	case sf::Keyboard::Left:
		if (m_player.getFillColor() == sf::Color(255, 255, 255, 0)) break;
		if (m_player.getPosition().x < 0.6) break;
		if (m_player.getPosition().y > 6.f) break;

		m_player.MoveLeft();
		break;
	}
}

//! Function to toggle debug draw
/*!
\toggle debug draw
*/
void Game::toggleDebug()
{
	m_debug = !m_debug;
}
