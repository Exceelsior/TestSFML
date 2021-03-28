#pragma once
#include "SFML/Graphics.hpp"
#include "Utils.h"

//Classe Entité contenant les infos de position, vitesse, direction de déplacement, et forme

class Entity {

private:
	float _positionX;
	float _positionY;

	sf::Vector2f _moveDirection;
	float _moveSpeed;

protected:
	sf::Shape* _shape; //protected sinon on ne peut pas le modifier dans la classe fille Ball (trop con d'avoir oublié ça :/ )

public:

	//constructeur
	Entity(float Xposition, float Yposition);

	//destructeur
	~Entity();


	void SetPosition(sf::Vector2f position);
	sf::Vector2f GetPosition() { return sf::Vector2f(_positionX, _positionY); };
	
	sf::Vector2f GetMoveDirection() { return _moveDirection; };
	void SetMoveDirection(sf::Vector2f velocity) { _moveDirection = velocity; };

	void SetMoveSpeed(float movespeed) { _moveSpeed = movespeed; };
	float GetMoveSpeed() { return _moveSpeed; };

	sf::Shape* GetShape() { return _shape; };

};