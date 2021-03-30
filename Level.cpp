#include "Level.h"

Level::Level(int sizeX, int sizeY) {

	for (int i = 0; i < sizeX; i++) {
		for (int j = 0; j < sizeY; j++) {

			_bricksList.push_back(Brick(sf::Vector2f(_windowWidth / 2, _windowHeight / 2), sf::Vector2f(50, 25), rand() % 4 + 1));
		}
	}
}

void Level::DrawLevel(sf::Window window){

	auto it = _bricksList.begin();
	while (it != _bricksList.end()) {
		//*it;
	}
}