#pragma once

#include <SFML\Graphics.hpp>
#include "TextureHolder.h"
#include "Grid.h"

class Engine
{
private:
	TextureHolder m_TextureHolder;

	// A regular RenderWindow
	sf::RenderWindow m_Window;
	sf::View m_MainView;
	sf::View m_GameOverView;
	sf::View m_WinView;

	sf::Texture m_gameOverTexture;
	sf::Texture m_winTexture;
	
	sf::Sprite m_winSprite;


	// The grid (will hold everything else)
	Grid m_Grid;

	//Dirt = 0, Boulder = 1, Diamond = 2, Exit = 3, Player = 4
	int m_levelOne[10][10] = { 
		{ 4,0,0,0,0,0,0,0,0,0 },
		{ 0,0,0,0,0,0,0,0,0,0 },
		{ 0,0,0,0,0,0,2,0,0,0 },
		{ 0,0,0,0,0,0,0,0,0,0 },
		{ 0,0,0,1,0,0,0,0,0,0 },
		{ 1,2,0,0,0,0,0,0,0,0 },
		{ 0,1,0,0,0,0,0,0,0,0 },
		{ 0,0,0,0,0,0,0,0,0,0 },
		{ 0,0,0,0,0,0,0,0,0,0 },
		{ 0,0,0,0,0,0,0,0,0,3 }
	};

	int m_levelTwo[10][10] = {
		{ 4,0,0,0,0,0,0,0,0,0 },
		{ 0,0,1,0,0,0,0,0,0,0 },
		{ 0,0,0,0,0,0,0,0,0,0 },
		{ 0,0,0,0,0,0,1,0,2,0 },
		{ 0,0,0,0,0,0,0,0,0,0 },
		{ 0,0,0,0,0,0,0,0,0,0 },
		{ 0,0,0,0,1,0,0,0,0,0 },
		{ 0,0,0,0,2,1,0,0,0,0 },
		{ 0,0,0,0,0,0,0,0,0,0 },
		{ 0,0,0,0,0,2,0,0,0,3 }
	};

	int m_levelThree[10][10] = {
		{ 4,0,0,1,0,0,2,0,0,0 },
		{ 0,0,0,1,0,1,0,0,0,0 },
		{ 0,0,0,0,0,0,0,0,0,0 },
		{ 0,0,0,0,0,0,0,0,0,0 },
		{ 0,2,0,0,0,0,1,0,0,0 },
		{ 0,0,0,0,0,0,0,0,0,0 },
		{ 0,0,2,0,0,0,0,0,0,0 },
		{ 0,0,1,0,0,0,0,0,0,0 },
		{ 0,0,0,2,0,0,0,0,0,0 },
		{ 0,0,0,0,0,0,0,0,0,3 } 
	};

	int m_levelFour[10][10] = { 
		{ 4,0,0,0,0,1,0,2,0,0 },
		{ 0,0,0,0,0,1,0,0,0,0 },
		{ 0,0,0,0,0,0,0,0,0,0 },
		{ 0,0,0,0,0,0,0,0,0,0 },
		{ 0,0,0,0,0,0,0,0,2,0 },
		{ 0,0,1,0,0,0,0,0,0,0 },
		{ 0,1,2,1,0,0,0,0,0,0 },
		{ 0,0,0,0,2,0,0,0,0,0 },
		{ 0,0,0,0,0,0,0,0,0,0 },
		{ 0,0,0,0,0,0,0,0,0,3 }
	};

	int m_levelFive[10][10] = {  
		{ 4,0,0,0,0,0,1,0,2,0 },
		{ 0,0,0,0,0,0,0,1,0,0 },
		{ 0,0,0,0,0,0,0,0,2,0 },
		{ 0,0,0,0,2,0,0,1,0,0 },
		{ 0,0,0,1,0,0,0,0,0,0 },
		{ 0,0,0,1,0,0,0,1,0,0 },
		{ 0,0,0,0,0,0,0,0,2,0 },
		{ 0,0,0,0,0,0,0,0,0,0 },
		{ 0,0,0,1,0,2,0,0,0,0 },
		{ 0,0,0,0,0,0,0,0,0,3 }
	};

	void LoadLevel(int currentLevel);
	void SpawnLevel(int levelToLoad[10][10]);
	bool IsGameover = false;
	bool HasWon = false;

	int m_currentLevel = 1;

	// Private functions for internal use only:
private:
	void input();
	void update(float dtAsSeconds);
	void draw();

public:
	// The Engine Constructor
	Engine();

	// Run will call all the private functions
	void run();
};