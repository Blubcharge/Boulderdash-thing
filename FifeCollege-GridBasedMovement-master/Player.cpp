#include "stdafx.h"
#include "Player.h"
#include "Grid.h"
#include "FallingObject.h"
#include "ExitObject.h"


// Constructor
Player::Player(sf::Texture& _texture)
	: GridSprite(_texture, GridObject::PLAYER)
{
	
}



// Handle player movement
bool Player::input(const sf::Event& _event)
{
	// Mark that we have received our input
	m_receivedInput = true;

	if (_event.type == sf::Event::KeyPressed)
	{
		// Handle movement
		if (_event.key.code == sf::Keyboard::Up
			|| _event.key.code == sf::Keyboard::Down
			|| _event.key.code == sf::Keyboard::Left
			|| _event.key.code == sf::Keyboard::Right)
		{
			int targetX = m_gridX;
			int targetY = m_gridY;

			if (_event.key.code == sf::Keyboard::Up)
			{
				--targetY;
			}
			else if (_event.key.code == sf::Keyboard::Down)
			{
				++targetY;
			}
			else if (_event.key.code == sf::Keyboard::Left)
			{
				--targetX;
			}
			else if (_event.key.code == sf::Keyboard::Right)
			{
				++targetX;
			}

			// Get the object currently in our target Cell
			GridObject* targetCellObject = m_grid->GetObject(targetX, targetY);

			//handles if player move into different types of objects
			// NOTE: This will automatically delete whatever GridObject is in the target cell!
			if (targetCellObject == nullptr || targetCellObject->GetType() == GridObject::DIRT)
				m_grid->MoveObject(m_gridX, m_gridY, targetX, targetY, true);
			else if (targetCellObject != nullptr && targetCellObject->GetType() == GridObject::DIAMOND)
			{
				m_grid->MoveObject(m_gridX, m_gridY, targetX, targetY, true);
			}

			else if (targetCellObject != nullptr && targetCellObject->GetType() == GridObject::BOULDER)
			{
				//if boulder and key pressed left/right push both boulder and player
				if (_event.key.code == sf::Keyboard::Right && m_grid->GetObject(targetX + 1, targetY) == nullptr)
				{
					m_grid->MoveObject(m_gridX + 1, m_gridY, targetX + 1, targetY, true);
					m_grid->MoveObject(m_gridX, m_gridY, targetX, targetY, true);
				}
				else if (_event.key.code == sf::Keyboard::Left && m_grid->GetObject(targetX - 1, targetY) == nullptr)
				{
					m_grid->MoveObject(m_gridX - 1, m_gridY, targetX - 1, targetY, true);
					m_grid->MoveObject(m_gridX, m_gridY, targetX, targetY, true);
				}

			}
			//block if exit not open
			else if (targetCellObject != nullptr && targetCellObject->GetType() == GridObject::EXIT && m_grid->diamondsOnScreen <= 0)
			{
				targetCellObject->ReachedNextLevel = true;
			}
			// Return true since we handled some input
			return true;
		}
	}
}