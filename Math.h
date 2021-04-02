#pragma once
#include "SFML/Graphics.hpp"
#include <cmath>

//Classe contenant des méthodes de calcul sympas

//Utile pour créer les vecteurs normalisés entre la position de la souris et la position des balles
sf::Vector2f CreateNormalizedVector(sf::Vector2f vector1, sf::Vector2f vector2);
sf::Vector2f CreateNormalizedVector(sf::Vector2i vector1, sf::Vector2f vector2);

void RotateSpriteToMouse(sf::Shape &shape, sf::Window &window); //Utile pour tourner la tourelle vers la souris