#pragma once
#include "Entity.h"


class Brick : public Entity {

private:

	float _life;
	sf::Vector2f _size;

public:

	//Constructeur
	Brick(sf::Vector2f position, sf::Vector2f size);

};