#pragma once
#include "Entity.h"
#include "Canon.h"
#include "Brick.h"
#include <iterator>
#include <list>

class Level {

private:
	std::list <Brick> _bricksList;

public:

	Level(int sizeX, int sizeY);
	void DrawLevel(sf::Window window);
};