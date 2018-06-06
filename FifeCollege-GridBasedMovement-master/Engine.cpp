#include "stdafx.h"
#include "Engine.h"
#include "GridSprite.h"
#include "Player.h"
#include "FallingObject.h"
#include "ExitObject.h"

using namespace sf;

Engine::Engine()
	: m_Grid(10,10,64.0f,64.0f) // Set your grid size here!
{
	// Get the game screen resolution
	// and creste an SFML window and View
	Vector2f resolution;
	resolution.x = VideoMode::getDesktopMode().width;
	resolution.y = VideoMode::getDesktopMode().height;

	//set game screen to the current resolution and run game in windowed mode
	m_Window.create(VideoMode(resolution.x, resolution.y),
		"Grid Based Movement Example",
		Style::Titlebar);
	//set framrate limit to 60 FPS
	m_Window.setFramerateLimit(60);

	// Initialise the different views
	m_MainView.reset(FloatRect(0, 0, resolution.x, resolution.y));
	m_GameOverView.reset(FloatRect(0, 0, resolution.x, resolution.y));
	m_WinView.reset(FloatRect(0, 0, resolution.x, resolution.y));

	//load and set texture for winning
	m_winTexture = TextureHolder::GetTexture("graphics/win.jpg");
	m_winSprite.setTexture(m_winTexture);

	// Set the grid position so grid is centered
	sf::Vector2f gridPosition(0,0);
	gridPosition.x = 0.5f*resolution.x -m_Grid.CELL_WIDTH  * 0.5f *(float)m_Grid.GRID_SIZE_X;
	gridPosition.y = 0.5f*resolution.y -m_Grid.CELL_HEIGHT * 0.5f *(float)m_Grid.GRID_SIZE_Y;
	m_Grid.SetPosition(gridPosition);

	//Loads currently selected level
	LoadLevel(m_currentLevel);
}

void Engine::run()
{
	// Timing
	Clock clock;

	while (m_Window.isOpen())
	{
		Time dt = clock.restart();

		// Make a float from the delta time
		float dtAsSeconds = dt.asSeconds();

		// Call each part of the game loop in turn
		input();
		update(dtAsSeconds);
		draw();
	}
}

void Engine::LoadLevel(int currentLevel)
{

	//selects what the current level is
	switch (currentLevel) {
	case 1:
		SpawnLevel(m_levelOne);
		break;
	case 2:
		SpawnLevel(m_levelTwo);
		break;
	case 3:
		SpawnLevel(m_levelThree);
		break;

	case 4:
		SpawnLevel(m_levelFour);
		break;

	case 5:
		SpawnLevel(m_levelFive);
		break;

	}

}

void Engine::SpawnLevel(int levelToLoad[10][10])
{
	//loop through all the grid tiles and set their texture depending on the predefined level layout
	for (int x = 0; x < 10; x++)
	{
		for (int y = 0; y < 10; y++)
		{
			switch (levelToLoad[x][y])
			{
			case 0:

				m_Grid.SetObject(x, y, new GridSprite(TextureHolder::GetTexture("graphics/dirt.png"), GridObject::DIRT), true);
				break;
			case 1:
				m_Grid.SetObject(x, y, new FallingObject(TextureHolder::GetTexture("graphics/boulder.png"), GridObject::BOULDER), true);
				break;
			case 2:
				m_Grid.SetObject(x, y, new FallingObject(TextureHolder::GetTexture("graphics/diamond.png"), GridObject::DIAMOND), true);
				break;
			case 3:
				m_Grid.SetObject(x, y, new ExitObject(TextureHolder::GetTexture("graphics/exit_locked.png"), GridObject::EXIT), true);
				break;
			case 4:
				m_Grid.SetObject(x, y, new Player(TextureHolder::GetTexture("graphics/player_down_01.png")));

			}
		}
	}
}