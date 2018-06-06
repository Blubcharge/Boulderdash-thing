#include "stdafx.h"
#include "FallingObject.h"
#include "Grid.h"

//a function to handle the falling of the boulder and diamonds
void FallingObject::update(const float& _dtAsSeconds)
{

	//tracks theh cell bellow the current one in the loop
	GridObject* targetCellObject = m_grid->GetObject(m_gridX, m_gridY + 1);
	m_isFalling = CheckIfFalling(targetCellObject);

	//random decider for what side to fall
	int randSide = rand() % 2;
	if (randSide == 0)
	{
		m_chosenSide = false;
	}
	else
	{
		m_chosenSide = true;
	}

	//if object is falling
	if (m_isFalling)
	{
		//update frame counter
		m_framesSinceLastUpdate -= _dtAsSeconds;
		if (m_framesSinceLastUpdate <= 0)
		{

			if (m_type == Type::BOULDER)
			{
				//if target cell is not empty and ists type is either a boulder or diamond
				if ((targetCellObject != nullptr) && (targetCellObject->GetType() == Type::BOULDER || targetCellObject->GetType() == Type::DIAMOND))
				{
					//picks a side to move depending by above
					if (m_chosenSide)
					{
						//checks for a player in  target cell
						if (targetCellObject->GetType() == Type::PLAYER)
						{
							//makes player killed true and moves current tile to new location
							HasKilledPlayer = true;
						}
						m_grid->MoveObject(m_gridX, m_gridY, m_gridX + 1, m_gridY + 1, true);
					}
					else
					{
						//checks for a player in  target cell
						if (targetCellObject->GetType() == Type::PLAYER)
						{
							//makes player killed true and moves current tile to new location
							HasKilledPlayer = true;
						}
						m_grid->MoveObject(m_gridX, m_gridY, m_gridX - 1, m_gridY + 1, true);
					}

					//resets ability to see if a space is clear
					m_leftSideClear = false;
					m_rightSideClear = false;
				}
				//checks for a player in  target cell
				else if (targetCellObject != nullptr && targetCellObject->GetType() == Type::PLAYER)
				{
					//makes player killed true and moves current tile to new location
					HasKilledPlayer = true;
					m_grid->MoveObject(m_gridX, m_gridY, m_gridX, m_gridY + 1, true);
				}
				//checks if target cell is empty
				else if (targetCellObject == nullptr)
				{
					m_grid->MoveObject(m_gridX, m_gridY, m_gridX, m_gridY + 1, true);
				}
			}
			//handles the diamond
			else if (m_type == Type::DIAMOND)
			{
				//checks for a player in  target cell
				if (targetCellObject != nullptr && targetCellObject->GetType() == Type::PLAYER)
				{
					//makes player killed true and moves current tile to new location
					HasKilledPlayer = true;
					m_grid->MoveObject(m_gridX, m_gridY, m_gridX, m_gridY+1, true);
				}
				else
				{
					//moves tile to a new location 
					m_grid->MoveObject(m_gridX, m_gridY, m_gridX, m_gridY + 1, true);
				}
			}
			//updates the frame counter
			m_framesSinceLastUpdate = m_targetFramesPerUpdate;
		}

	}


}

bool FallingObject::CheckIfFalling(GridObject* targetObject)
{

	if (m_type == Type::BOULDER)
	{
		//check for clear space on left side of current tile
		if (m_grid->GetObject(m_gridX - 1, m_gridY) == nullptr && m_grid->GetObject(m_gridX - 1, m_gridY - 1) == nullptr)
		{
			m_leftSideClear = true;
		}
		//check for clear space on Right side of current tile
		if (m_grid->GetObject(m_gridX + 1, m_gridY) == nullptr && m_grid->GetObject(m_gridX + 1, m_gridY - 1) == nullptr)
		{
			m_rightSideClear = true;
		}
		//if either of the side clear allow for movment
		if (m_rightSideClear || m_leftSideClear)
		{
			return true;
		}
	}
	if (targetObject == nullptr || targetObject->GetType() == Type::PLAYER)
	{
		return true;
	}
	return false;
	
}