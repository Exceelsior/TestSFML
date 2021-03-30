#pragma once
#include "Ball.h"
#include "Canon.h"
#include "Brick.h"
#include <iterator>
#include <list>

class Level {

private:
	std::list <Brick*> _brickList;
	std::list <Ball*> _ballList;


public:

	Level(int sizeX, int sizeY);
	void DrawLevel(sf::RenderWindow &window);
};