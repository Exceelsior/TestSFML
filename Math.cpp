#include "Math.h"

sf::Vector2f Math::CreateNormalizedVector(sf::Vector2f vector1, sf::Vector2f vector2) {

	float _xOffset = vector1.x - vector2.x;
	float _yOffset = vector1.y - vector2.y;
	float _newVectorNorm = sqrt(pow(_xOffset, 2) + pow(_yOffset, 2));
	return ((vector1 - vector2) / _newVectorNorm);

}

sf::Vector2f Math::CreateNormalizedVector(sf::Vector2i vector1, sf::Vector2f vector2) {

	float _xOffset = vector1.x - vector2.x;
	float _yOffset = vector1.y - vector2.y;
	float _newVectorNorm = sqrt(pow(_xOffset, 2) + pow(_yOffset, 2));
	return ((sf::Vector2f(vector1.x, vector1.y) - vector2) / _newVectorNorm);

}