#pragma once

#include "GridSprite.h"

class ExitObject : public GridSprite 
{

public:
	//texture for holding exit tile
	ExitObject(sf::Texture& _texture, GridObject::Type _type) : GridSprite(_texture, _type) { }

	void update(const float& _dtAsSeconds) override;


protected:
	//indicator for when exit is open
	bool m_isExitOpen = false;

};
