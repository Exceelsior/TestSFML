#include "Level.h"

Level::Level(int sizeX, int sizeY) {

	for (int i = 0; i < sizeX; i++) {
		for (int j = 0; j < sizeY; j++) {

			_brickList.push_back(new Brick(sf::Vector2f(i*_windowWidth/sizeX, j*_windowWidth/(2*sizeY)),
				sf::Vector2f(_windowWidth/sizeX, _windowHeight /(3*sizeY)), rand() % 4 + 1));
		}
	}
}

void Level::DrawLevel(sf::RenderWindow &window){

	auto _itBricks = _brickList.begin();
	while (_itBricks != _brickList.end()) {
		Brick* currentBrick = *_itBricks;
		if (currentBrick->CheckIfHasBeenDestroyed()) {
			_itBricks = _brickList.erase(_itBricks);
		}
		else {
			window.draw(*currentBrick->GetShape());
			_itBricks++;
		}
	}

	auto _itBalls = _ballList.begin();

	while (_itBalls != _ballList.end()) {
		Ball* currentBall = *_itBalls;
		if (currentBall->CheckIfHasBeenDestroyed()) {
			_itBalls = _ballList.erase(_itBalls);
		}
		else {
			window.draw(*currentBall->GetShape());
			_itBalls++;
		}
	}



}