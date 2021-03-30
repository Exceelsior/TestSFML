#pragma once
#include "SFML/Graphics.hpp"



sf::Vector2f CreateNormalizedVector(sf::Vector2f vector1, sf::Vector2f vector2);
sf::Vector2f CreateNormalizedVector(sf::Vector2i vector1, sf::Vector2f vector2);

float ScalarProduct(sf::Vector2f vector1, sf::Vector2f vector2);

void RotateSpriteToMouse(sf::Shape &shape, sf::Window &window);