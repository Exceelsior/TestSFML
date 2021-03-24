#pragma once
#include "SFML/Graphics.hpp"

class Entity {

private:
	float _positionX;
	float _positionY;
	sf::Shape* _shape;

public:

	//constructeur
	Entity(float Xposition, float Yposition);

	//destructeur
	~Entity();


	void SetPosition(sf::Vector2f position);

	sf::Vector2f GetPosition() { return sf::Vector2f(_positionX, _positionY); };
	
	sf::Shape* GetShape() { return _shape; };

};