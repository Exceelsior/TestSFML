#pragma once
#include "SFML/Graphics.hpp"


class Math {

public :

	sf::Vector2f CreateNormalizedVector(sf::Vector2f vector1, sf::Vector2f vector2);
	sf::Vector2f CreateNormalizedVector(sf::Vector2i vector1, sf::Vector2f vector2);
};