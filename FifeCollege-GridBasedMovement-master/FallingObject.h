#pragma once

#include "GridSprite.h"
#include <ctime>

class FallingObject : public GridSprite
{

public:
	//holds the falling object texture
	FallingObject(sf::Texture& _texture, GridObject::Type _type) : GridSprite(_texture, _type)
	{
		srand(time(0));
	}
	//call for update
	void update(const float& _dtAsSeconds) override;

	//if player gets killed
	bool GetKilledPlayer()
	{
		return m_killedPlayer;
	}

private:
	//internal use variables
	int m_framesSinceLastUpdate = 40;
	int m_targetFramesPerUpdate = 40;
	bool m_isFalling = false;
	bool m_killedPlayer = false;

	bool m_leftSideClear = false;
	bool m_rightSideClear = false;
	//false = fall left, true = fall right
	bool m_chosenSide;


	bool CheckIfFalling(GridObject* targetObject);

};