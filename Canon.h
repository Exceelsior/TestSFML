#pragma once
#include "Entity.h"

class Canon: public Entity {

private:

	sf::Vector2f _size;


public:
	
	Canon(sf::Vector2f position, sf::Vector2f size);

};