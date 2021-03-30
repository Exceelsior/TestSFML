#include "Math.h"
#include <cmath>

sf::Vector2f CreateNormalizedVector(sf::Vector2f vector1, sf::Vector2f vector2) {

	float _xOffset = vector1.x - vector2.x;
	float _yOffset = vector1.y - vector2.y;
	float _newVectorNorm = sqrt(pow(_xOffset, 2) + pow(_yOffset, 2));
	return ((vector1 - vector2) / _newVectorNorm);

}

sf::Vector2f CreateNormalizedVector(sf::Vector2i vector1, sf::Vector2f vector2) {

	float _xOffset = vector1.x - vector2.x;
	float _yOffset = vector1.y - vector2.y;
	float _newVectorNorm = sqrt(pow(_xOffset, 2) + pow(_yOffset, 2));
	return ((sf::Vector2f(vector1.x, vector1.y) - vector2) / _newVectorNorm);

}

float ScalarProduct(sf::Vector2f vector1, sf::Vector2f vector2) {

	float _xSum = vector1.x + vector2.x;
	float _ySum = vector1.y + vector2.y;

	return _xSum + _ySum;
}

void RotateSpriteToMouse(sf::Shape &shape, sf::Window &window) {
	
	sf::Vector2f shapePosition = shape.getPosition();

	const float pi = 3.14159265;

	float dx = sf::Mouse::getPosition(window).x - shapePosition.x;
	float dy = sf::Mouse::getPosition(window).y - shapePosition.y;

	float rotation = ((atan2(dy, dx)) * 180 / pi) +90;

	shape.setRotation(rotation);
}