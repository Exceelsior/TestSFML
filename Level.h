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
	std::list <Ball*> _ammoList;

	int _magSize = 4;
	int _maxAmmo = 20;
	
	Canon* _canon;

	int _levelArray[10][10] = {
	{0,2,2,3,3,3,3,2,2,0},
	{2,1,0,0,0,0,0,0,1,2},
	{2,1,0,2,3,3,2,0,1,2},
	{2,1,0,3,4,4,3,0,1,2},
	{2,1,0,3,4,4,3,0,1,2},
	{2,1,0,2,3,3,2,0,1,2},
	{2,1,0,0,0,0,0,0,1,2},
	{2,1,0,0,0,0,0,0,1,2},
	{2,1,1,0,2,2,0,1,1,2},
	{0,2,2,0,3,3,0,2,2,0}
	};


    public:

	Level();
	void DrawLevel(sf::RenderWindow &window, float deltaTime);
	void MoveAndCollideItems(sf::RenderWindow&, float deltaTime);
	void ShootBalls(sf::Event &event, sf::RenderWindow &window);

	std::list <Ball*> GetBallList() { return _ballList; };

};