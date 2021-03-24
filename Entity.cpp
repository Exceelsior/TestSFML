#include "Entity.h"


//Constructeur

Entity::Entity(float positionX, float positionY) : _positionX(positionX), _positionY(positionY) {}


//Destructeur

Entity::~Entity() {
	//Do something ?
}

void Entity::SetPosition(sf::Vector2f position) {
	_positionX = position.x; //est-ce que ça sert vraiment ?
	_positionY = position.y;
	_shape->setPosition(_positionX, _positionY);
}


