#pragma once
#include "Entity.h"
#include "Utils.h"
#include "Canon.h"

class Ball:public Entity {
	
private:

	sf::Vector2f _speedDirection;
	float _moveSpeed = 500;

	int _ballSize = 20; //taille de base de la balle
	float _ballRadius; //taille en fonction de la taille de l'écran (est-ce vraiment utile ?)

	sf::Vector2f _startPosition;
	sf::CircleShape* _shape;

	bool _isReadyToBeLaunched;

public:
	
	//constructeur
	Ball(float ballRadius, sf::Vector2f startPosition);

	//destructeur
	//???

	sf::Vector2f GetSpeedDirection() { return _speedDirection; };


	void SetSpeedDirection(sf::Vector2f velocity) { _speedDirection = velocity; };

	void SetMoveSpeed(float movespeed) { _moveSpeed = movespeed; };
	float GetMoveSpeed() { return _moveSpeed; };


	void SetReadyToLaunch(bool isReady) { _isReadyToBeLaunched = isReady; };
	bool CheckIfReadyToBeLaunched() { return _isReadyToBeLaunched; };

	float GetBallSize() { return _ballSize; };


};