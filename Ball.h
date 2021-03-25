#pragma once
#include "Entity.h"
#include "Brick.h"

class Ball :public Entity {

private:

	int _ballSize = 20; //taille de base de la balle
	float _ballRadius; //taille en fonction de la taille de l'écran (est-ce vraiment utile ?)

	sf::Vector2f _startPosition;

	bool _isReadyToBeLaunched;
	bool _hasBeenLaunched;


public:

	//constructeur
	Ball(float ballRadius, sf::Vector2f startPosition);

	//destructeur
	//???

	sf::Vector2f GetStartPosition() { return _startPosition; };

	void SetReadyToLaunch(bool isReady) { _isReadyToBeLaunched = isReady; };
	bool CheckIfReadyToBeLaunched() { return _isReadyToBeLaunched; };

	void SetLaunched(bool hasBeenLaunched) { _hasBeenLaunched = hasBeenLaunched; };
	bool CheckIfHasBeenLaunched() { return _hasBeenLaunched; };

	float GetBallSize() { return _ballSize; };

	bool CheckWallCollision();

	void BrickCollision(Brick& brick);

};